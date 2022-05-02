#include "tooldialog.h"
#include "ui_tooldialog.h"
#include <QMessageBox>
#include <QTextStream>
#include "utils/models/otofilelistmodel.h"
#include <kira/dialogs/tableviewdialog.h>
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

    //Deal with command line mode
    auto args = qApp->arguments();
    if (args.count() > 1){
        args.removeFirst();
        auto buttons = ui->buttonBox->standardButtons().setFlag(QDialogButtonBox::Reset, false);
        ui->buttonBox->setStandardButtons(buttons);
        ui->switchLoadModeButton->hide();
        //As we have direct save widget here. We name it multiple save widget because of historical reason.
        ui->stackedSaveWidget->setCurrentIndex(batchModePageIndex);
        ui->otoMultipleSaveWidget->setInfoText(tr("Only \"save to source file\" is supported in command line mode. Extra save path functionality is also disabled."));
        if (args.count() == 1){
            ui->stackedLoadWidget->setCurrentIndex(singleModePageIndex);
            ui->otoLoadWidget->setFileName(args.at(0));
            ui->otoLoadWidget->load();
        }
        else{
            ui->stackedLoadWidget->setCurrentIndex(batchModePageIndex);//Batch mode
            ui->otoMultipleLoadWidget->loadFiles(args);
            ui->otoMultipleLoadWidget->disableModify();
        }
    }

    reAssignWidgetHandles();

    //askOtoData callback handle
    connect(optionWidget, &ToolOptionWidget::askOtoData, optionWidget, [this](int askId){
         if (isSingleMode())
             optionWidget->askOtoDataCallback(askId, QList({ui->otoLoadWidget->getEntryList()}));
         else
             optionWidget->askOtoDataCallback(askId, ui->otoMultipleLoadWidget->entryLists());
    });

    setWindowTitle(adapter->getToolName());
    refreshStackedWidgetSize(ui->stackedLoadWidget);
    refreshStackedWidgetSize(ui->stackedSaveWidget);

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &ToolDialog::buttonBoxClicked);
    connect(ui->switchLoadModeButton, &QPushButton::clicked, this, &ToolDialog::toggleMode);
}

void ToolDialog::reAssignWidgetHandles()
{
    //Use last() to choose the newest widgets.
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

void ToolDialog::accept()
{
    if (!((isSingleMode() && ui->otoLoadWidget->isEntryListReaded()) || (isBatchMode() && ui->otoMultipleLoadWidget->count() > 0)))
    {
        QMessageBox::critical(this, tr("File is not loaded"), tr("Oto.ini has not been loaded. Please load it and try again."));
        return;
    }

    bool success = false;

    auto userOptions = optionWidget->getOptions();

    auto saveOptions = isBatchMode() ? ui->otoMultipleSaveWidget->getOptions() : ui->otoSaveWidget->getOptions();
    saveOptions.setOption("precision", ui->precisionSpinBox->value());

    auto options = OptionContainer::combine(userOptions, saveOptions, "save/");

    if (isSingleMode()){
        success = doWork(ui->otoLoadWidget->getEntryList(), ui->otoLoadWidget->fileName(),
                         options, this);
    }
    else {
        success = doWork(ui->otoMultipleLoadWidget->entryLists(), ui->otoMultipleLoadWidget->fileNames(),
                         options, this);
    }

    if (success){
        QMessageBox::information(this, {}, tr("Operation completed successfully."));
        QDialog::accept();
    }
}

void ToolDialog::reset()
{
    presetWidgetContainer->reset();
    resetOto();
}

void ToolDialog::resetOto()
{
    ui->otoLoadWidget->reset();
    ui->otoMultipleLoadWidget->reset();

    refreshOptionWidgetEnableState();
}

void ToolDialog::buttonBoxClicked(QAbstractButton* button)
{
    auto stdCode = ui->buttonBox->standardButton(button);
    if (stdCode == QDialogButtonBox::Reset)
    {
        reset();
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
        ui->saveOptionsContainer->setEnabled(state);
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
    auto toolOptions = options;
    toolOptions.setOption("load/fileName", srcFileName);

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
        result = saveOtoFileWithErrorInform(entryListWorking, precision, isSaveToSrc ? srcFileName : fileName, tr("Save processing result"), dialogParent);
    }
    return result;
}

bool ToolDialog::doWork(const QVector<OtoEntryList>& srcLists, const QStringList srcFileNames, const OptionContainer& options, QWidget* dialogParent)
{
    Q_ASSERT(srcLists.count() == srcFileNames.count());

    auto saveOptions = options.extract("save/");
    auto toolOptions = options;

    QVector<OtoEntryList> results{};

    for (int i = 0; i < srcLists.count(); ++i){
        OtoEntryList entryListWorking{};
        OtoEntryList secondSaveList{};

        toolOptions.setOption("load/fileName", srcFileNames.at(i));
        try {
            adapter->getWorkerInstance()->doWork(srcLists.at(i), entryListWorking, secondSaveList, toolOptions);
        }
        catch (const ToolException& e){
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText(tr("Stopped because file %1 (at %2) was failed to process. All files are remained unchanged. Please check and try again.")
                           .arg(srcFileNames.at(i)).arg(i + 1));
            msgBox.setInformativeText(e.info());
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            return false;
        }
        results.append(entryListWorking);
    }

    auto model = new OtoFileListWithPreviousModel(this);
    for (int i = 0; i < srcLists.count(); ++i){
        model->addData(srcFileNames.at(i), results.at(i), srcLists.at(i));
    }
    auto dialog = new QDialog(this);
    dialog->setWindowTitle(tr("Confirm changes"));

    auto rootLayout = new QVBoxLayout(dialog);

    auto label = new QLabel(tr("These are changes that will be applied to oto data. Click \"OK\" to confirm, \"Cancel\" to discard these changes."), dialog);
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
    auto showDiffButton = buttonBox->addButton(tr("Show difference for selected file"), QDialogButtonBox::ActionRole);
    connect(showDiffButton, &QPushButton::clicked, this, [contentView, results, srcLists, srcFileNames, dialogParent, saveOptions](){
        auto currentIndex = contentView->currentIndex().row();
        auto currentSrc = srcLists.at(currentIndex);
        auto currentResult = results.at(currentIndex);
        Misc::showOtoDiffDialog(currentSrc, currentResult, saveOptions.getOption("precision").toInt(),
                                tr("Differences of %1 (at %2)").arg(srcFileNames.at(currentIndex)).arg(currentIndex + 1),
                                tr("These are changes that will be applied to %1 （at %2).").arg(srcFileNames.at(currentIndex)).arg(currentIndex + 1),
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
            bool success = saveOtoFileWithErrorInform(results.at(i), decimalAccuracy, isSaveToSrc ? srcFileNames.at(i) : fileName, tr("Save processing result"), dialogParent);
            if (!success){
                QMessageBox::critical(dialogParent, tr("Error occured while saving"),
                                      tr("As %1 (at %2) can not be saved, the process is stopped. Files before it has been saved.").arg(srcFileNames.at(i)).arg(i + 1));
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
        QMessageBox::critical(dialogParent, tr("Failed to save"), [&]() -> QString{
            QString result;
            QTextStream stream(&result);
            stream << tr("Error occured when saving %1.").arg(fileName);
            if (!usage.isEmpty())
                stream << tr("The file is meant to be used for %1.").arg(usage);
            stream << tr("Error information: %1").arg(errorString);
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
