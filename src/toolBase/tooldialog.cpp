#include "tooldialog.h"
#include "ui_tooldialog.h"
#include <QMessageBox>
#include <QTextStream>
#include "utils/models/otofilelistmodel.h"
#include "utils/dialogs/tableviewdialog.h"
#include "utils/models/otofilelistwithpreviousmodel.h"
#include "utils/misc/misc.h"
#include "presetwidgetcontainer.h"

ToolDialog::ToolDialog(ToolDialogAdapter* adapter, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolDialog),
    adapter(adapter)
{
    ui->setupUi(this);
    connect(ui->otoLoadWidget, &OtoFileLoadWidget::loaded, this, &ToolDialog::refreshOptionWidgetEnableState);
    connect(ui->otoLoadWidget, &OtoFileLoadWidget::resetted, this, &ToolDialog::refreshOptionWidgetEnableState);
    connect(ui->otoMultipleLoadWidget, &OtoFileMultipleLoadWidget::dataChanged, this, &ToolDialog::refreshOptionWidgetEnableState);
    adapter->replaceUIWidgets(ui->rootLayout);

    reAssignWidgetHandles();

    setWindowTitle(adapter->getToolName());
    refreshStackedWidgetSize(ui->stackedLoadWidget);
    refreshStackedWidgetSize(ui->stackedSaveWidget);

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &ToolDialog::buttonBoxClicked);
    connect(ui->switchLoadModeButton, &QPushButton::clicked, this, &ToolDialog::toggleMode);
}

void ToolDialog::reAssignWidgetHandles()
{
    //Use last() to choose the newest widgets.
    //ui->optionWidget = ui->optionLayout->parentWidget()->findChildren<ToolOptionWidget*>(QString(), Qt::FindDirectChildrenOnly).last();
    presetWidgetContainer = ui->optionLayout->parentWidget()->findChildren<PresetWidgetContainer*>(QString(), Qt::FindDirectChildrenOnly).last();
    optionWidget = presetWidgetContainer->optionWidget();
    //TODO: may change to a individual handle later
    ui->otoSaveWidget = ui->rootLayout->parentWidget()
            ->findChild<QWidget*>("stackedSaveWidget")->
            findChild<QWidget*>("singleSave")->
            findChildren<OtoFileSaveWidget*>(QString(), Qt::FindDirectChildrenOnly).last();
    Q_ASSERT(ui->otoSaveWidget);
}

ToolDialog::~ToolDialog()
{
    delete ui;
}

void ToolDialog::otoFileLoaded()
{
    ui->optionGroupBox->setEnabled(true);
    Q_ASSERT(optionWidget->isEnabled());
    ui->otoSaveWidget->setEnabled(true);
}

void ToolDialog::ToolDialog::accept()
{
    if (!((isSingleMode() && ui->otoLoadWidget->isEntryListReaded()) || (isBatchMode() && ui->otoMultipleLoadWidget->count() > 0)))
    {
        QMessageBox::critical(this, tr("文件未加载"), tr("您还没有加载oto.ini文件。请加载后重试。"));
        return;
    }

    bool success = false;
    if (isSingleMode()){
        success = doWork(ui->otoLoadWidget->getEntryList(), ui->otoLoadWidget->fileName(), OptionContainer::combine(optionWidget->getOptions(), ui->otoSaveWidget->getOptions(), "save/"), this);
    }
    else {
        success = doWork(ui->otoMultipleLoadWidget->entryLists(), ui->otoMultipleLoadWidget->fileNames(), OptionContainer::combine(optionWidget->getOptions(), ui->otoSaveWidget->getOptions(), "save/"), this);
    }

    if (success){
        QMessageBox::information(this, tr("操作成功完成"), tr("操作成功完成。"));
        QDialog::accept();
    }
}

void ToolDialog::reset()
{
    resetOptions();
    resetOto();
}

void ToolDialog::resetOto()
{
    ui->otoLoadWidget->reset();
    ui->otoMultipleLoadWidget->reset();

    refreshOptionWidgetEnableState();
}

void ToolDialog::resetOptions()
{
    //optionWidget->setOptions({});
    presetWidgetContainer->reset();
    ui->otoSaveWidget->setOptions({});
}

void ToolDialog::buttonBoxClicked(QAbstractButton* button)
{
    auto stdCode = ui->buttonBox->standardButton(button);
    if (stdCode == QDialogButtonBox::Reset)
    {
        reset();
    }
    if (stdCode == QDialogButtonBox::RestoreDefaults)
    {
        resetOptions();
    }
}

void ToolDialog::toggleMode()
{
    if (isSingleMode()){
        switchToBatchMode();
    }
    else{
        switchToSingleMode();
    }
}

void ToolDialog::refreshOptionWidgetEnableState()
{
    auto setEnableState = [&](bool state){
        ui->optionGroupBox->setEnabled(state);
        ui->stackedSaveWidget->setEnabled(state);
    };
    if (isSingleMode()){
        setEnableState(ui->otoLoadWidget->isEntryListReaded());
    }
    else {
        setEnableState(ui->otoMultipleLoadWidget->count() > 0);
    }
}

bool ToolDialog::doWork(const OtoEntryList& srcList, const QString& srcFileName, const OptionContainer& options, QWidget* dialogParent)
{
    OtoEntryList entryListWorking{};
    OtoEntryList secondSaveList{};

    auto saveOptions = options.extract("save/");
    auto& toolOptions = options;

    auto result = adapter->doWork(srcList, entryListWorking, secondSaveList, toolOptions, dialogParent);
    if (result)
    {
        auto precision = saveOptions.getOption("precision").toInt();
        auto isSecondFileNameAvailable = saveOptions.getOption("isSecondFileNameAvailable").toBool();
        auto isSecondFileNameUsed = saveOptions.getOption("isSecondFileNameUsed").toBool();
        if (isSecondFileNameAvailable && isSecondFileNameUsed){
            auto secondFileName = saveOptions.getOption("secondFileName").toString();
            auto secondFileNameUsage = saveOptions.getOption("secondFileNameUsage").toString();
            result = saveOtoFileWithErrorInform(secondSaveList, precision, secondFileName, secondFileNameUsage, dialogParent);
            if (!result)
                return false;
        }
        auto isSaveToSrc = saveOptions.getOption("isSaveToSrc").toBool();
        auto fileName = saveOptions.getOption("fileName").toString();
        result = saveOtoFileWithErrorInform(entryListWorking, precision, isSaveToSrc ? srcFileName : fileName, tr("保存处理结果"), dialogParent);
    }
    return result;
}

bool ToolDialog::doWork(const QList<OtoEntryList>& srcLists, const QStringList srcFileNames, const OptionContainer& options, QWidget* dialogParent)
{
    Q_ASSERT(srcLists.count() == srcFileNames.count());

    auto saveOptions = options.extract("save/");
    auto& toolOptions = options;

    QList<OtoEntryList> results{};

    for (int i = 0; i < srcLists.count(); ++i){
        OtoEntryList entryListWorking{};
        OtoEntryList secondSaveList{};

        if ((!adapter->doWork(srcLists.at(i), entryListWorking, secondSaveList, toolOptions)) && srcLists.count() > 1)
        {
            QMessageBox::critical(dialogParent, tr("处理失败"), tr("文件 %1 （位于第 %2）没有成功被处理，于是进程终止。所有文件都没有被修改。").arg(srcFileNames.at(i)).arg(i + 1));
            return false;
        }
        results.append(entryListWorking);
    }

    auto model = new OtoFileListWithPreviousModel(this);
    for (int i = 0; i < srcLists.count(); ++i){
        model->addData(srcFileNames.at(i), results.at(i), srcLists.at(i));
    }
    auto dialog = new QDialog(this);
    dialog->setWindowTitle(tr("确认更改"));

    auto rootLayout = new QVBoxLayout(dialog);

    auto label = new QLabel(tr("以下显示了根据您的要求要对原音设定数据执行的修改。点击“确定”来确认此修改，点击“取消”以取消本次操作。"), dialog);
    rootLayout->addWidget(label);

    auto contentView = new QTableView(dialog);
    contentView->setModel(model);
    contentView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    contentView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    contentView->resizeColumnsToContents();
    rootLayout->addWidget(contentView);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
    auto showDiffButton = buttonBox->addButton(tr("显示选中的文件的差异"), QDialogButtonBox::ActionRole);
    connect(showDiffButton, &QPushButton::clicked, this, [contentView, results, srcLists, srcFileNames, dialogParent, saveOptions](){
        auto currentIndex = contentView->currentIndex().row();
        auto currentSrc = srcLists.at(currentIndex);
        auto currentResult = results.at(currentIndex);
        Misc::showOtoDiffDialog(currentSrc, currentResult, saveOptions.getOption("precision").toInt(),
                                tr("%1 的差异（位于第 %2 项）").arg(srcFileNames.at(currentIndex)).arg(currentIndex + 1),
                                tr("以下显示了根据您的要求要对 %1（位于第 %2 项）执行的修改。").arg(srcFileNames.at(currentIndex)).arg(currentIndex + 1),
                                dialogParent,
                                Misc::Determine,
                                QDialogButtonBox::Ok);
    });
    rootLayout->addWidget(buttonBox);

    if (dialog->exec()){
        for (int i = 0; i < srcLists.count(); ++i){
            auto decimalAccuracy = saveOptions.getOption("secondFileNameUsage").toInt();
            auto isSaveToSrc = saveOptions.getOption("isSaveToSrc").toBool();
            auto fileName = saveOptions.getOption("fileName").toString();
            bool success = saveOtoFileWithErrorInform(results.at(i), decimalAccuracy, isSaveToSrc ? srcFileNames.at(i) : fileName, tr("保存处理结果"), dialogParent);
            if (!success){
                QMessageBox::critical(dialogParent, tr("保存时出现错误"), tr("无法保存 %1（位于第 %2 项），操作终止，该项之前的项已被保存。").arg(srcFileNames.at(i)).arg(i + 1));
                return false;
            }
        }
        return true;
    };
    return false;
}

void ToolDialog::refreshStackedWidgetSize(QStackedWidget* stackedWidget)
{
    for (int i = 0; i < stackedWidget->count(); i++){
        auto currentWidget = stackedWidget->widget(i);
        auto sizePolicy = currentWidget->sizePolicy();
        if (i != stackedWidget->currentIndex())
        {
            sizePolicy.setVerticalPolicy(QSizePolicy::Ignored);
        }
        else{
            sizePolicy.setVerticalPolicy(QSizePolicy::Preferred);
        }
        stackedWidget->widget(i)->setSizePolicy(sizePolicy);
    }
    stackedWidget->adjustSize();
}

bool ToolDialog::isBatchMode() const
{
    return ui->stackedLoadWidget->currentIndex() == batchModePageIndex;
}

bool ToolDialog::isSingleMode() const
{
    return !isBatchMode();
}

void ToolDialog::switchToBatchMode()
{
    if (isBatchMode())
        return;
    switchModePrivate(batchModePageIndex);
}

void ToolDialog::switchModePrivate(int pageIndex)
{
    resetOto();
    ui->stackedLoadWidget->setCurrentIndex(pageIndex);
    ui->stackedSaveWidget->setCurrentIndex(pageIndex);
    refreshStackedWidgetSize(ui->stackedLoadWidget);
    refreshStackedWidgetSize(ui->stackedSaveWidget);
}

bool ToolDialog::saveOtoFileWithErrorInform(const OtoEntryList& entryList, int decimalAccuracy, const QString& fileName, const QString& usage, QWidget* dialogParent)
{
    QString errorString;
    auto result = OtoEntryFunctions::writeOtoListToFile(fileName, entryList, decimalAccuracy, nullptr, &errorString);
    if (!result)
    {
        QMessageBox::critical(dialogParent, tr("保存失败"), [&]() -> QString{
            QString result;
            QTextStream stream(&result);
            stream << tr("在保存 %1 时发生错误。").arg(fileName);
            if (!usage.isEmpty())
                stream << tr("该文件的用途是 %1。").arg(usage);
            stream << tr("遇到的错误是：%1").arg(errorString);
            return result;
        }());
    }
    return result;
}

void ToolDialog::switchToSingleMode()
{
    if (isSingleMode())
        return;
    switchModePrivate(singleModePageIndex);
}
