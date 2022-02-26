#include "mergeotootolistmodifyworker.h"
#include "mergeotooptionwidget.h"

MergeOtoOtoListModifyWorker::MergeOtoOtoListModifyWorker(QObject *parent) : OtoListModifyWorker(parent)
{

}

void MergeOtoOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                         OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)
    auto otherOtoLoaded = options.getOption("otherOtoLoaded").toBool();
    if (!otherOtoLoaded)
        throw ToolException(tr("The oto file to merge from has not been loaded."));
    auto otherOtoList = options.getOption("otherOtoList").value<OtoEntryList>();
    auto mergeStrtegy = (MergeOtoOptionWidget::MergeStrategy) options.getOption("mergeStrategy", MergeOtoOptionWidget::Replace).toInt();

    resultOtoList = srcOtoList;
    for (const auto& otherEntry : qAsConst(otherOtoList)){
        auto findResult = fplus::find_first_idx_by([otherEntry](const OtoEntry& srcEntry){
            return srcEntry.alias() == otherEntry.alias();
        },resultOtoList);
        if (findResult.is_just()){
            if (mergeStrtegy == MergeOtoOptionWidget::Replace){
                resultOtoList[findResult.unsafe_get_just()] = otherEntry;
                continue;
            }
            else if (mergeStrtegy == MergeOtoOptionWidget::Skip)
                continue;
        }
        resultOtoList.append(otherEntry);
    }
}
