#include "tooldialog.h"
#include "ui_tooldialog.h"
#ifdef SHINE5402OTOBOX_TEST
#include <QTimer>
#endif
#include <QMessageBox>
#include <QTextStream>

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
    reAssignUIWidgets();
    setWindowTitle(adapter->getToolName());
    refreshStackedWidgetSize(ui->stackedLoadWidget);
    refreshStackedWidgetSize(ui->stackedSaveWidget);

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &ToolDialog::buttonBoxClicked);
    connect(ui->switchLoadModeButton, &QPushButton::clicked, this, &ToolDialog::toggleMode);
}

void ToolDialog::reAssignUIWidgets()
{
    //Use last() to choose the newest widgets.
    ui->optionWidget = ui->optionLayout->parentWidget()->findChildren<ToolOptionWidget*>(QString(), Qt::FindDirectChildrenOnly).last();
    Q_ASSERT(ui->optionWidget);
    //FIXME:
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
    Q_ASSERT(ui->optionWidget->isEnabled());
    ui->otoSaveWidget->setEnabled(true);
}

void ToolDialog::ToolDialog::accept()
{
    if ((!(isSingleMode() && ui->otoLoadWidget->isEntryListReaded())) || (!(isBatchMode() && ui->otoMultipleLoadWidget->count() > 0)))
    {
        QMessageBox::critical(this, tr("文件未加载"), tr("您还没有加载oto.ini文件。请加载后重试。"));
        return;
    }

    bool success = false;
    if (isSingleMode()){
        success = doWork(ui->otoLoadWidget->getEntryList(), ui->otoLoadWidget->fileName(), ui->otoSaveWidget, ui->optionWidget, this);
    }
    else {
        success = doWork(ui->otoMultipleLoadWidget->entryLists(), ui->otoMultipleLoadWidget->fileNames(), ui->otoMultipleSaveWidget, ui->optionWidget, this);
    }

    if (success){
#ifndef SHINE5402OTOBOX_TEST
        QMessageBox::information(this, tr("操作成功完成"), tr("操作成功完成。"));
#endif
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
    ui->optionWidget->setOptions(ToolOptions{});
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

bool ToolDialog::doWork(const OtoEntryList& srcList, const QString& srcFileName, const OtoFileSaveWidgetAbstract* saveWidget, const ToolOptionWidget* optionWidget, QWidget* dialogParent)
{
    OtoEntryList entryListWorking{};
    OtoEntryList secondSaveList{};
    auto options = optionWidget->getOptions();

    auto saveOtoFileWithErrorInform = [&](const OtoEntryList& entryList, const QString& fileName, const QString& usage) -> bool{
        QString errorString;
        auto result = OtoEntryFunctions::writeOtoListToFile(fileName, entryList, nullptr, &errorString);
        if (!result)
        {
#ifdef SHINE5402OTOBOX_TEST
            Q_ASSERT(false);
#endif
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
    };

    auto result = adapter->doWork(srcList, entryListWorking, secondSaveList, options, dialogParent);
    if (result)
    {
        if (saveWidget->isSecondFileNameAvailable() && saveWidget->isSecondFileNameUsed()){
            result = saveOtoFileWithErrorInform(secondSaveList, saveWidget->secondFileName(), saveWidget->secondFileNameUsage());
            if (!result)
                return false;
        }
        result = saveOtoFileWithErrorInform(entryListWorking, saveWidget->isSaveToSrc() ? srcFileName : saveWidget->fileName(), tr("保存处理结果"));
    }
    return result;
}

bool ToolDialog::doWork(const QList<OtoEntryList>& srcLists, const QStringList srcFileNames, const OtoFileSaveWidgetAbstract* saveWidget, const ToolOptionWidget* optionWidget, QWidget* dialogParent)
{
    Q_ASSERT(srcLists.count() == srcFileNames.count());
    bool success = false;
    for (int i = 0; i < srcLists.count(); ++i){
        success &= doWork(srcLists.at(i), srcFileNames.at(i), saveWidget, optionWidget, dialogParent);
        if ((!success) && srcLists.count() > 1)
        {
            QMessageBox::critical(dialogParent, tr("处理失败"), tr("文件 %1 （位于第 %2）没有成功被处理，于是进程终止。在其之前的文件已被处理。").arg(srcFileNames.at(i)).arg(i + 1));
        }
    }
    return success;
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

void ToolDialog::switchToSingleMode()
{
    if (isSingleMode())
        return;
    switchModePrivate(singleModePageIndex);
}
