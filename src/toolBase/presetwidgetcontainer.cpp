#include "presetwidgetcontainer.h"
#include "ui_presetwidgetcontainer.h"
#include "tooloptionwidget.h"
#include "presetmanager.h"
#include <QMessageBox>
#include <QInputDialog>
#include "../lib/misc/qballontip.h"
#include <QFileDialog>
#include <QJsonDocument>

//TODO:name restriction

static QString getNameInDirtyState(QString text, bool dirty){
    const auto dirtyFlag = QStringLiteral("[*] ");
    auto isTextDirty = text.startsWith(dirtyFlag);
    if (dirty && !isTextDirty)
        text = dirtyFlag + text;
    if (!dirty && isTextDirty)
        text.remove(0, dirtyFlag.size());
    return text;
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

    connect(ui->presetComboBox, qOverload<int>(&QComboBox::currentIndexChanged), [this]{
        doResetToPreset();
        resetComboBoxDirtyState();
    });
    //connect(ui->presetComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &PresetWidgetContainer::resetToPreset);
    connect(ui->resetButton, &QToolButton::clicked, this, &PresetWidgetContainer::resetToPreset);
    connect(ui->renameButton, &QToolButton::clicked, this, &PresetWidgetContainer::renamePreset);
    connect(ui->saveButton, &QToolButton::clicked, this, &PresetWidgetContainer::savePreset);
    connect(ui->addButton, &QToolButton::clicked, this, &PresetWidgetContainer::addPreset);
    connect(ui->deleteButton, &QToolButton::clicked, this, &PresetWidgetContainer::deletePreset);
    connect(ui->importButton, &QToolButton::clicked, this, &PresetWidgetContainer::importPreset);
    connect(ui->exportButton, &QToolButton::clicked, this, &PresetWidgetContainer::exportPreset);

    connect(optionWidget, &ToolOptionWidget::userSettingsChanged, [this](){
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

void PresetWidgetContainer::doResetToPreset()
{
    optionWidget_->setOptionsJson(getCurrentPreset().content);
}

void PresetWidgetContainer::resetToPreset()
{
    if (currentDirty)
    {
        auto reply = QMessageBox::question(this, {}, tr("确认要重置当前设置到预设内容吗？"));
        if (reply == QMessageBox::No)
            return;
    }
    doResetToPreset();
}

void PresetWidgetContainer::renamePreset()
{
    if (currentDirty)
    {
        QMessageBox::critical(this, {}, tr("当前设置和预设中的设置不同，请保存当前设置或重置为预设内设置后再进行重命名。"));
        return;
    }
    if (!checkCurrentPresetBuiltIn())
        return;

    auto preset = getCurrentPreset();
    bool ok = false;
    auto newName = QInputDialog::getText(this, tr("重命名"), tr("为预设指定新名称："), QLineEdit::Normal, preset.name, &ok);
    if (ok && !newName.isEmpty())
    {
        auto originalName = preset.name;
        preset.name = newName;
        preset.updateMeta(optionWidget_);
        PresetManager::getManager()->replacePreset(targetName(), originalName, preset);
    }
}

void PresetWidgetContainer::savePreset()
{
    if (!currentDirty){
        QBalloonTip::showBalloon(qApp->style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxInformation), tr("无需保存"), tr("当前设置和预设内设置一致，不需要进行保存操作。"), this, QCursor::pos(), 3000);
        return;
    }
    if (!checkCurrentPresetBuiltIn())
        return;
    auto preset = getCurrentPreset();
    preset.content = optionWidget_->getOptionsJson();
    preset.updateMeta(optionWidget_);
    PresetManager::getManager()->replacePreset(targetName(), preset.name, preset);
    setCurrentDirty(false);
    QBalloonTip::showBalloon(qApp->style()->standardIcon(QStyle::StandardPixmap::SP_MessageBoxInformation), tr("保存完毕"), tr("已经将工作设置保存到预设“%1”中。").arg(preset.name), this, QCursor::pos(), 3000);
}

void PresetWidgetContainer::addPreset()
{
    bool ok = false;
    auto name = QInputDialog::getText(this, tr("添加预设"), tr("为新预设指定名称："), QLineEdit::Normal, {}, &ok);
    if (ok && !name.isEmpty())
    {
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
    if (getCurrentPreset().isBuiltIn())
    {
        QMessageBox::critical(this, {}, tr("内置预设无法被删除。"));
        return;
    }
    auto reply = QMessageBox::question(this, tr("删除预设"), tr("确定要删除预设%1吗？").arg(getCurrentPreset().name));
    if (reply == QMessageBox::Yes)
    {
        PresetManager::getManager()->removePreset(targetName(), getCurrentPreset().name);
        reloadComboBoxItems();
        ui->presetComboBox->setCurrentIndex(0);
    }
}

void PresetWidgetContainer::importPreset()
{
    auto fileName = QFileDialog::getOpenFileName(this, tr("选择要导入的预设描述文件"), {}, tr("预设描述文件 (*.json);;所有文件 (*.*)"));
    QFile file{fileName};
    if (!file.open(QFile::Text | QFile::ReadOnly)){
        QMessageBox::critical(this, {}, tr("无法打开预设文件。"));
    }
    auto content = QJsonDocument::fromJson(file.readAll());
    if (content.isNull() || content.isEmpty() || !content.isObject()){
        QMessageBox::critical(this, {}, tr("预设文件中没有有效的内容。"));
    }
    auto preset = Preset::fromJson(content.object());
    PresetManager::getManager()->appendPreset(targetName(), preset);
    reloadComboBoxItems();
    ui->presetComboBox->setCurrentText(preset.name);
}

void PresetWidgetContainer::exportPreset()
{
    auto fileName = QFileDialog::getSaveFileName(this, tr("要把预设描述文件保存到……"), {}, tr("预设描述文件 (*.json)"));
    QFile file{fileName};
    if (!file.open(QFile::Text | QFile::WriteOnly)){
        QMessageBox::critical(this, {}, tr("无法打开预设文件。"));
    }
    if (file.write(QJsonDocument(getCurrentPreset().toJson()).toJson()) == -1){
        QMessageBox::critical(this, {}, tr("写入文件时出现问题。"));
    }
}

void PresetWidgetContainer::resetComboBoxDirtyState()
{
    //Reset dirty indicator for all preset when user change preset
    //The reason to reset all is that we cannot know before user change, and Qt don't tell us which one is being changed from, so...
    for (auto i = 0; i < ui->presetComboBox->count(); ++i){
        setComboBoxItemTextDirtyState(i, false);
    }
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
        return tr("%1%2").arg(preset.name).arg(PresetManager::getManager()->isBuiltIn(targetName(), preset) ? tr("[内置]") : "");
    }, PresetManager::getManager()->presets(targetName())).toList());
    //ui->presetComboBox->setCurrentText(currPreset.name);
}

void PresetWidgetContainer::setCurrentDirty(bool value)
{
    currentDirty = value;
    refreshComboBoxForDirtyState();
}

void PresetWidgetContainer::refreshComboBoxForDirtyState()
{
    setComboBoxItemTextDirtyState(ui->presetComboBox->currentIndex(), currentDirty);
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

bool PresetWidgetContainer::checkCurrentPresetBuiltIn()
{
    if (isCurrentPresetBuiltIn())
    {
        QMessageBox::critical(this, {}, tr("内置预设无法被修改，请保存为用户预设后再做修改。"));
        return false;
    }
    return true;
}
