#include "overlapbatchsetdialogadapter.h"
#include "overlapbatchsetdialogoptionwidget.h"
#include "utils/models/otolistshowvaluechangemodel.h"
#include "utils/dialogs/showotolistdialog.h"
#include <QMessageBox>

OverlapBatchSetDialogAdapter::OverlapBatchSetDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{

}

void OverlapBatchSetDialogAdapter::setupSpecificUIWidgets(QLayout* rootLayout)
{
    replaceOptionWidget(rootLayout, new OverlapBatchSetDialogOptionWidget(rootLayout->parentWidget()));
}

bool OverlapBatchSetDialogAdapter::doWork(const OtoFileLoadWidget* loadWidget, const OtoFileSaveWidget* saveWidget, const ToolOptionWidget* optionWidget, QWidget* dialogParent)
{
    const auto entryList = loadWidget->getEntryList();
    auto entryListWorking = entryList;
    auto options = qobject_cast<const OverlapBatchSetOptions*>(optionWidget->getOptions(this));

    QVector<int> matched;
    //匹配开头并设置为指定数值
    if (options->setOverlapStartWith)
    {
        for (int i = 0; i < entryListWorking.count(); ++i)
        {
            auto entry = entryListWorking.at(i);
            for (auto s : options->startWithPatternList)
            {
                if (entry.alias().startsWith(s) || (options->startWithMatchStartAlias && entry.alias().startsWith("- " + s)))
                {
                    entry.setOverlap(options->overlapStartWith);
                    entryListWorking.replace(i, entry);
                    matched.append(i);
                    break;
                }
            }
        }
    }
    //设置三分之一
    if (options->makeOneThird)
    {
        for (int i = 0; i < entryListWorking.count(); ++i)
        {
            if (!matched.contains(i))
            {
                auto entry = entryListWorking.at(i);
                entry.setOverlap(entry.preUtterance() / 3);
                entryListWorking.replace(i, entry);
            }
        }
    }

    //显示差异和向用户确认
    auto model = new OtoListShowValueChangeModel(&entryList, &entryListWorking, OtoEntry::Overlap ,this);
    auto dialog = new ShowOtoListDialog(model, dialogParent);
    dialog->setWindowTitle(tr("确认对Overlap的更改"));
    dialog->setLabel(tr("以下显示了根据您的要求要对原音设定数据执行的修改。点击“确定”来确认此修改，点击“取消”以取消本次操作。"));
    auto code = dialog->exec();
    if (code == QDialog::Rejected)
        return false;

    //写入文件
    QFile file(saveWidget->isSaveToCustom() ? saveWidget->fileName() : loadWidget->fileName());
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
        auto code = OtoEntryFunctions::writeOtoListToFile(file, entryListWorking);
        if (code == -1)
        {
#ifdef SHINE5402OTOBOX_TEST
            Q_ASSERT(false);
#endif
            QMessageBox::critical(dialogParent, tr("保存失败"), tr("无法保存文件。"));
        }
        else
        {
#ifndef SHINE5402OTOBOX_TEST
            QMessageBox::information(dialogParent, tr("成功"), tr("文件已经保存好了。"));
#endif

        }
    }
    else{
#ifdef SHINE5402OTOBOX_TEST
        Q_ASSERT(false);
#endif
        QMessageBox::critical(dialogParent, tr("无法打开指定路径"), tr("无法打开 %1。").arg(file.fileName()));
    }
    return true;
}
