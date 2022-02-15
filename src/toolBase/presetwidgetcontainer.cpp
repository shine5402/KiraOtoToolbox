#include "presetwidgetcontainer.h"
#include "ui_presetwidgetcontainer.h"
#include "tooloptionwidget.h"
#include "presetmanager.h"
#include <QMessageBox>
#include <QInputDialog>
#include <kira/widgets/qballontip.h>
#include <QFileDialog>
#include <QJsonDocument>
#include <kira/i18n/translationmanager.h>

namespace {
    const auto dirtyFlag = QStringLiteral("[*] ");

    bool isNameDirty(const QString& name){
       return name.startsWith(dirtyFlag);
    }

    QString getNameInDirtyState(QString name, bool dirty){
        if (dirty && !isNameDirty(name))
            name = dirtyFlag + name;
        if (!dirty && isNameDirty(name))
            name.remove(0, dirtyFlag.size());
        return name;
    }

    bool isNameValid(const QString& name){
        return !(name == QCoreApplication::translate("PresetManager", "Default") || name.startsWith(dirtyFlag));
    }
}

PresetWidgetContainer::PresetWidgetContainer(const QMetaObject& optionWidgetMetaObj, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresetWidgetContainer),
    optionWidgetMetaObj(optionWidgetMetaObj)
{
    ui->setupUi(this);

    //Initialize option widget and replace it
    auto optionWidget = qobject_cast<ToolOptionWidget *>(optionWidgetMetaObj.newInstance(Q_ARG(QWidget*, this)));
    optionWidget->setOptions({});
    delete ui->mainLayout->replaceWidget(ui->optionWidget, optionWidget);
    ui->optionWidget->deleteLater();
    ui->optionWidget = optionWidget;
    this->optionWidget_ = optionWidget;

    reloadComboBoxItems();

    connect(ui->presetComboBox, qOverload<int>(&QComboBox::currentIndexChanged),
            this, &PresetWidgetContainer::doResetToPreset);
    connect(ui->resetButton, &QToolButton::clicked, this, &PresetWidgetContainer::resetToPreset);
    connect(ui->renameButton, &QToolButton::clicked, this, &PresetWidgetContainer::renamePreset);
    connect(ui->saveButton, &QToolButton::clicked, this, &PresetWidgetContainer::savePreset);
    connect(ui->addButton, &QToolButton::clicked, this, &PresetWidgetContainer::addPreset);
    connect(ui->deleteButton, &QToolButton::clicked, this, &PresetWidgetContainer::deletePreset);
    connect(ui->importButton, &QToolButton::clicked, this, &PresetWidgetContainer::importPreset);
    connect(ui->exportButton, &QToolButton::clicked, this, &PresetWidgetContainer::exportPreset);

    connect(optionWidget, &ToolOptionWidget::userSettingsChanged, this, [this](){
        setCurrentDirty(true);
    });
}

PresetWidgetContainer::~PresetWidgetContainer()
{
    delete ui;
}

ToolOptionWidget* PresetWidgetContainer::optionWidget() const
{
    return optionWidget_;
}

void PresetWidgetContainer::setWorkingOptions(OptionContainer options)
{
    optionWidget()->setOptions(options);
    setCurrentDirty(true);
}

void PresetWidgetContainer::reset()
{
    ui->presetComboBox->setCurrentIndex(0);
    doResetToPreset();
}

void PresetWidgetContainer::doResetToPreset()
{
    auto currPreset = getCurrentPreset();
    auto json = getCurrentPreset().content;
    if (currPreset.version < optionWidget_->optionJsonVersion())
        json = optionWidget_->updateOptionJsonFrom(currPreset.version, json);
    optionWidget_->setOptionsJson(json);
    resetComboBoxDirtyState();
}

void PresetWidgetContainer::resetToPreset()
{
    if (currentDirty())
    {
        auto reply = QMessageBox::question(this, {}, tr("Confirm reset working settings to preset?"));
        if (reply == QMessageBox::No)
            return;
    }
    doResetToPreset();
}

void PresetWidgetContainer::renamePreset()
{
    if (currentDirty())
    {
        QMessageBox::critical(this, {}, tr("Working settings is changed from preset. Please save or reset first."));
        return;
    }
    if (!checkCurrentPresetBuiltInForUserModify())
        return;

    auto preset = getCurrentPreset();
    bool ok = false;
    auto name = QInputDialog::getText(this, tr("Rename"), tr("Specify new name for preset:"), QLineEdit::Normal, preset.name, &ok);
    if (ok && !name.isEmpty())
    {
        if (!isNameValid(name))
        {
            QMessageBox::critical(this, {}, tr("The given name is invalid. Please retry with a different one."));
            return;
        }
        auto originalName = preset.name;
        preset.name = name;
        preset.updateMeta(optionWidget_);
        PresetManager::getManager()->replacePreset(targetName(), originalName, preset);
    }
}

void PresetWidgetContainer::doSavePreset()
{
    auto preset = getCurrentPreset();
    preset.content = optionWidget_->getOptionsJson();
    preset.updateMeta(optionWidget_);
    PresetManager::getManager()->replacePreset(targetName(), preset);
    setCurrentDirty(false);
}

void PresetWidgetContainer::savePreset()
{
    if (!checkCurrentPresetBuiltInForUserModify())
        return;
    if (!currentDirty()){
        QBalloonTip::showBalloon(qApp->style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxInformation),
                                 tr("No need to save"), tr("Current working setting is same with preset."), this, QCursor::pos(), 3000);
        return;
    }
    doSavePreset();
    QBalloonTip::showBalloon(qApp->style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxInformation),
                             tr("Save complete"), tr("Current working setting is saved to \"%1\".").arg(getCurrentPreset().name), this, QCursor::pos(), 3000);
}

void PresetWidgetContainer::addPreset()
{
    bool ok = false;
    auto name = QInputDialog::getText(this, tr("Add preset"), tr("Specify name for new preset:"), QLineEdit::Normal, {}, &ok);
    if (ok && !name.isEmpty())
    {
        if (!isNameValid(name))
        {
            QMessageBox::critical(this, {}, tr("The given name is invalid. Please retry with a different one."));
            return;
        }
        Preset preset;
        preset.content = optionWidget_->getOptionsJson();
        preset.name = name;
        preset.updateMeta(optionWidget_);
        PresetManager::getManager()->appendPreset(targetName(), preset);
        reloadComboBoxItems();
        ui->presetComboBox->setCurrentText(name);
    }
}

void PresetWidgetContainer::deletePreset()
{
    if (PresetManager::getManager()->isBuiltIn(targetName(), getCurrentPreset()))
    {
        QMessageBox::critical(this, {}, tr("Built-in preset can't be removed."));
        return;
    }
    auto reply = QMessageBox::question(this, tr("Delete preset"), tr("Relly want to remove preset %1?").arg(getCurrentPreset().name));
    if (reply == QMessageBox::Yes)
    {
        PresetManager::getManager()->removePreset(targetName(), getCurrentPreset().name);
        reloadComboBoxItems();
        ui->presetComboBox->setCurrentIndex(0);
    }
}

void PresetWidgetContainer::importPreset()
{
    auto fileName = QFileDialog::getOpenFileName(this, tr("Choose a preset file to import"), {},
                                                 tr("Preset description file (*.json);;All files (*.*)"));
    if (fileName.isEmpty())
        return;
    QFile file{fileName};
    if (!file.open(QFile::Text | QFile::ReadOnly)){
        QMessageBox::critical(this, {}, tr("Can't open the preset file."));
    }
    auto content = QJsonDocument::fromJson(file.readAll());
    if (content.isNull() || content.isEmpty() || !content.isObject()){
        QMessageBox::critical(this, {}, tr("The given preset file contains no valid content."));
    }
    auto preset = Preset::fromJson(content.object());

    if (!isNameValid(preset.name))
    {
        QMessageBox::critical(this, {}, tr("Preset file contains invalid preset name\"%1\", so it can not be imported.").arg(preset.name));
    }
    if (PresetManager::getManager()->exist(targetName(), preset))
    {
        auto reply = QMessageBox::warning(this, {}, tr("Name \"%1\" already exists. Replace it?").arg(preset.name), QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No)
            return;
        if (reply == QMessageBox::Yes)
        {
            if (PresetManager::getManager()->isBuiltIn(targetName(), preset.name))
            {
                QMessageBox::critical(this, {}, "\"%1\" is a built-in preset. It can't be replaced.");
                return;
            }
            PresetManager::getManager()->replacePreset(targetName(), preset);
            ui->presetComboBox->setCurrentText(preset.name);
            return;
        }
    }
    if (optionWidget_->optionJsonVersion() < preset.version){
        QMessageBox::critical(this, {}, tr("The given preset file contains a preset whose version is newer than what currently used."));
    }

    PresetManager::getManager()->appendPreset(targetName(), preset);
    reloadComboBoxItems();
    ui->presetComboBox->setCurrentText(preset.name);
}

void PresetWidgetContainer::exportPreset()
{
    if (PresetManager::getManager()->isBuiltIn(targetName(), getCurrentPreset()))
    {
        QMessageBox::critical(this, {}, tr("Built-in presets can't be exported. Please turn it into user preset and try again."));
        return;
    }
    if (currentDirty())
    {
        auto reply = QMessageBox::warning(this, {}, tr("Current working setting has not been saved. Save it into current preset before proceeding?\n"
"If not, original preset content other than working setting will be saved."),
                                          QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes)
            doSavePreset();
        if (reply == QMessageBox::Cancel)
            return;
    }
    auto fileName = QFileDialog::getSaveFileName(this, tr("Save preset description file to..."), {}, tr("Preset description file (*.json)"));
    if (fileName.isEmpty())
        return;
    QFile file{fileName};
    if (!file.open(QFile::Text | QFile::WriteOnly)){
        QMessageBox::critical(this, {}, tr("Can't open preset file."));
    }
    if (file.write(QJsonDocument(getCurrentPreset().toJson()).toJson()) == -1){
        QMessageBox::critical(this, {}, tr("Error occured when writing the file."));
    }
}

void PresetWidgetContainer::resetComboBoxDirtyState()
{
    //Reset dirty indicator for all preset when user change preset
    //The reason to reset all is that we cannot know before user change, and Qt don't tell us which one is being changed from, so...
    for (auto i = 0; i < ui->presetComboBox->count(); ++i){
        setComboBoxItemTextDirtyState(i, false);
    }
    //As we determine dirty state by text in combobox's currenttext, we implicitly change current dirty to false here.
}

QString PresetWidgetContainer::targetName() const
{
    return optionWidgetMetaObj.className();
}

void PresetWidgetContainer::reloadComboBoxItems()
{
    //auto currPreset = getCurrentPreset();
    ui->presetComboBox->clear();
    //Get presets and put their name into combobox
    ui->presetComboBox->addItems(fplus::transform([this](const Preset& preset)->QString{
        //So for built-in presets, it will show like "Preset 1 [Built-in]"
        return tr("%1%2").arg(preset.getI18nName(Translation::getCurrentInstalled().locale()), PresetManager::getManager()->isBuiltIn(targetName(), preset) ? tr(" [Built-in]") : "");
    }, PresetManager::getManager()->presets(targetName())).toList());
    //ui->presetComboBox->setCurrentText(currPreset.name);
}

bool PresetWidgetContainer::currentDirty()
{
    return isNameDirty(ui->presetComboBox->currentText());
}

void PresetWidgetContainer::setCurrentDirty(bool value)
{
    setComboBoxItemTextDirtyState(ui->presetComboBox->currentIndex(), value);
}

void PresetWidgetContainer::setComboBoxItemTextDirtyState(int id, bool dirty)
{
    auto model = ui->presetComboBox->model();
    auto index = model->index(id, 0);
    auto text = model->data(index).toString();

    model->setData(index, getNameInDirtyState(text, dirty), Qt::DisplayRole);
}

Preset PresetWidgetContainer::getCurrentPreset() const
{
    auto presets = PresetManager::getManager()->presets(targetName());
    auto currentIndex = ui->presetComboBox->currentIndex();
    if (presets.count() <= currentIndex || currentIndex < 0)
        return {};
    return presets.at(currentIndex);
}

bool PresetWidgetContainer::isCurrentPresetBuiltIn() const
{
    return PresetManager::getManager()->isBuiltIn(targetName(), getCurrentPreset());
}

bool PresetWidgetContainer::checkCurrentPresetBuiltInForUserModify()
{
    if (isCurrentPresetBuiltIn())
    {
        QMessageBox::critical(this, {}, tr("Built-in presets can't be modified. Please turn it into user preset and try again."));
        return false;
    }
    return true;
}
