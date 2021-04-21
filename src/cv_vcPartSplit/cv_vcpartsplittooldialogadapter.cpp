#include "cv_vcpartsplittooldialogadapter.h"
#include "cv_vcpartsplitoptionwidget.h"
#include "cv_vcpartsplitotolistmodifyworker.h"
#include "utils/misc/misc.h"

CV_VCPartSplitToolDialogAdapter::CV_VCPartSplitToolDialogAdapter(QObject *parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(CV_VCPartSplitOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(CV_VCPartSplitOptionWidget::staticMetaObject);
}

void CV_VCPartSplitToolDialogAdapter::replaceUIWidgets(QLayout* rootLayout)
{
    auto saveWidget = new OtoFileSaveWidgetWithSecondFileName;
    saveWidget->setSecondFileNameCheckBoxText("分离VC部到新文件：");
    saveWidget->setSecondFileNameUsage("保存分离出来的VC部");
    replaceSaveWidget(rootLayout, saveWidget);
    ToolDialogAdapter::replaceUIWidgets(rootLayout);
}

QString CV_VCPartSplitToolDialogAdapter::getToolName() const
{
    return tr("分离CV/VC部");
}

bool CV_VCPartSplitToolDialogAdapter::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options, QWidget* dialogParent)
{
    auto precision = options.getOption("save/precision").toInt();
    auto isSecondFileNameUsed = options.getOption("save/isSecondFileNameUsed").toBool();
    if (ToolDialogAdapter::doWork(srcOtoList, resultOtoList, secondSaveOtoList, options)){
        if (!(isSecondFileNameUsed && Misc::askUserWithShowOtoList(secondSaveOtoList, tr("分离出的VC部"), tr("以下 %1 条原音设定条目将会被保存至您所指定的位置。").arg(secondSaveOtoList.count()), dialogParent)))
        {
            return false;
        }
        return Misc::showOtoDiffDialog(srcOtoList, resultOtoList, precision,
                                      tr("确认更改"),
                                      tr("以下显示了根据您的要求要对原音设定数据执行的修改。点击“确定”来确认此修改，点击“取消”以取消本次操作。"),
                                      dialogParent, Misc::Diff);
    }
    return false;
}
