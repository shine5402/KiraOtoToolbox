#include "overlapbatchsetdialogadapter.h"
#include "overlapbatchsetdialogoptionwidget.h"
#include "utils/models/otolistshowvaluechangemodel.h"
#include "utils/dialogs/showotolistdialog.h"
#include "utils/dialogs/tableviewdialog.h"
#include <QMessageBox>

OverlapBatchSetDialogAdapter::OverlapBatchSetDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{

}

void OverlapBatchSetDialogAdapter::setupSpecificUIWidgets(QLayout* rootLayout)
{
    replaceOptionWidget(rootLayout, new OverlapBatchSetDialogOptionWidget(rootLayout->parentWidget()));
}

bool OverlapBatchSetDialogAdapter::doWorkAdapter(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* abstractOptions, QWidget* dialogParent)
{
    Q_UNUSED(secondSaveOtoList)
    auto options = qobject_cast<const OverlapBatchSetOptions*>(abstractOptions);

    QVector<int> matched;
    //匹配开头并设置为指定数值
    if (options->setOverlapStartWith)
    {
        for (int i = 0; i < resultOtoList.count(); ++i)
        {
            auto entry = resultOtoList.at(i);
            for (auto s : options->startWithPatternList)
            {
                if (entry.alias().startsWith(s) || (options->startWithMatchStartAlias && entry.alias().startsWith("- " + s)))
                {
                    entry.setOverlap(options->overlapStartWith);
                    resultOtoList.replace(i, entry);
                    matched.append(i);
                    break;
                }
            }
        }
    }
    //设置三分之一
    if (options->makeOneThird)
    {
        for (int i = 0; i < resultOtoList.count(); ++i)
        {
            if (!matched.contains(i))
            {
                auto entry = resultOtoList.at(i);
                entry.setOverlap(entry.preUtterance() / 3);
                resultOtoList.replace(i, entry);
            }
        }
    }

    //显示差异和向用户确认
    auto model = new OtoListShowValueChangeModel(&srcOtoList, &resultOtoList, OtoEntry::Overlap ,this);
    auto dialog = new TableViewDialog(dialogParent, model);
    dialog->setWindowTitle(tr("确认对Overlap的更改"));
    dialog->setLabel(tr("以下显示了根据您的要求要对原音设定数据执行的修改。点击“确定”来确认此修改，点击“取消”以取消本次操作。"));
    auto code = dialog->exec();
    if (code == QDialog::Rejected)
        return false;
    return true;
}

QString OverlapBatchSetDialogAdapter::getWindowTitle() const
{
    return tr("批量修改Overlap");
}
