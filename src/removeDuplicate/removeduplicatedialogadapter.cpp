#include "removeduplicatedialogadapter.h"
#include "removeduplicateoptionwidget.h"
#include "utils/models/otolistshowvaluechangemodel.h"
#include "utils/dialogs/showotolistdialog.h"
#include <QMessageBox>
#include "removeAffix/removeaffixotolistmodifyworker.h"
#include "orgnaizeduplicateotolistmodifyworker.h"
#include "removeduplicatemoduleotolistmodifyworker.h"
#include "utils/misc/misc.h"

RemoveDuplicateDialogAdapter::RemoveDuplicateDialogAdapter(QObject* parent) : ToolDialogAdapter(parent)
{
    setWorkerMetaObj(RemoveDuplicateModuleOtoListModifyWorker::staticMetaObject);
    setOptionWidgetMetaObj(RemoveDuplicateOptionWidget::staticMetaObject);
}

void RemoveDuplicateDialogAdapter::replaceUIWidgets(QLayout* rootLayout)
{
    replaceSaveWidget(rootLayout, new OtoFileSaveWidgetWithSecondFileNameAsDeleted(rootLayout->parentWidget()));
    ToolDialogAdapter::replaceUIWidgets(rootLayout);
}

bool RemoveDuplicateDialogAdapter::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options, QWidget* dialogParent)
{
    auto precision = options.getOption("save/precision").toInt();
    getWorkerInstance()->doWork(srcOtoList, resultOtoList, secondSaveOtoList, options);
    auto specificWorker = new RemoveDuplicateModuleOtoListModifyWorker(this);
    if ((!specificWorker->getOrganizeResult().isEmpty()) &&
            (!Misc::showOtoDiffDialog(srcOtoList, specificWorker->getOrganizeResult(), precision, tr("Result of removing duplicate entries"),
                                      tr("The emphasized entries will be renamed, in which unneeded ones will be removed in next step. Click \"OK\" to confirm, \"Cancel\" to discard these changes."),
                                      dialogParent,
                                      Misc::ValueChangeModel)))
        return false;
    if ((!secondSaveOtoList.isEmpty()) && (!Misc::askUserWithShowOtoList(secondSaveOtoList, tr("Oto entries to remove"),
                                                                         tr("These %1 oto entries will be removed, or be saved to the specified file. Click \"OK\" to confirm, \"Cancel\" to discard these changes.").arg(secondSaveOtoList.count()),
                                                                         dialogParent)))
        return false;
    return Misc::showOtoDiffDialog(srcOtoList, resultOtoList, precision,
                                   tr("Confirm changes"),
                                   tr("These are changes that will be applied to oto data. Click \"OK\" to confirm, \"Cancel\" to discard these changes."),
                                   dialogParent,
                                   Misc::Diff);
    return false;
}
