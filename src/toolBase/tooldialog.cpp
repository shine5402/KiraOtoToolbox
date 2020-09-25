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
    connect(ui->otoLoadWidget, &OtoFileLoadWidget::loaded, this, &ToolDialog::otoFileLoaded);
    adapter->replaceUIWidgets(ui->rootLayout);
    reAssignUIWidgets();
    setWindowTitle(adapter->getToolName());
}

void ToolDialog::reAssignUIWidgets()
{
    //Use last() to choose the newest widgets.
    ui->optionWidget = ui->optionLayout->parentWidget()->findChildren<ToolOptionWidget*>(QString(), Qt::FindDirectChildrenOnly).last();
    Q_ASSERT(ui->optionWidget);
    ui->otoSaveWidget = ui->rootLayout->parentWidget()->findChildren<OtoFileSaveWidget*>(QString(), Qt::FindDirectChildrenOnly).last();
    Q_ASSERT(ui->otoSaveWidget);
}

ToolDialog::~ToolDialog()
{
    delete ui;
}

void ToolDialog::otoFileLoaded()
{
    ui->optionGroupBox->setEnabled(true);
    //ui->optionWidget->setEnabled(true);
    Q_ASSERT(ui->optionWidget->isEnabled());
    ui->otoSaveWidget->setEnabled(true);
}

void ToolDialog::ToolDialog::accept()
{
    if (!ui->otoLoadWidget->isEntryListReaded())
    {
        QMessageBox::critical(this, tr("文件未加载"), tr("您还没有加载oto.ini文件。请加载后重试。"));
        return;
    }
    if (doWork(ui->otoLoadWidget->getEntryList(), ui->otoLoadWidget->fileName(), ui->otoSaveWidget, ui->optionWidget, this)){
#ifndef SHINE5402OTOBOX_TEST
    QMessageBox::information(this, tr("操作成功完成"), tr("操作成功完成。"));
#endif
        QDialog::accept();
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
        if (!success)
        {
            QMessageBox::critical(dialogParent, tr("处理失败"), tr("文件 %1 （位于第 %2）没有成功被处理，于是进程终止。在其之前的文件已被处理。").arg(srcFileNames.at(i)).arg(i + 1));
        }
    }
    return success;
}
