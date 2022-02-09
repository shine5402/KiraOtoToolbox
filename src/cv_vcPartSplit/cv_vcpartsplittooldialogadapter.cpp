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
    saveWidget->setSecondFileNameCheckBoxText("Extract VC part to: ");
    saveWidget->setSecondFileNameUsage("Save the VC part extracted");
    replaceSaveWidget(rootLayout, saveWidget);
    ToolDialogAdapter::replaceUIWidgets(rootLayout);
}

bool CV_VCPartSplitToolDialogAdapter::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options, QWidget* dialogParent)
{
    auto precision = options.getOption("save/precision").toInt();
    auto isSecondFileNameUsed = options.getOption("save/isSecondFileNameUsed").toBool();
    if (getWorkerInstance()->doWork(srcOtoList, resultOtoList, secondSaveOtoList, options)){
        if (isSecondFileNameUsed && !(Misc::askUserWithShowOtoList(secondSaveOtoList, tr("VC part extracted"), tr("These %1 oto entries will be save to location specified.").arg(secondSaveOtoList.count()), dialogParent)))
        {
            return false;
        }
        return Misc::showOtoDiffDialog(srcOtoList, resultOtoList, precision,
                                      tr("Confirm changes"),
                                      tr("These are changes that will be applied to oto data. Click \"OK\" to confirm, \"Cancel\" to discard these changes."),
                                      dialogParent, Misc::Diff);
    }
    return false;
}
