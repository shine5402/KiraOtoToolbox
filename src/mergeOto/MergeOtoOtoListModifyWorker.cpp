#include "MergeOtoOtoListModifyWorker.h"

#include <algorithm>

#include "MergeOtoOptionWidget.h"

MergeOtoOtoListModifyWorker::MergeOtoOtoListModifyWorker(QObject *parent) : OtoListModifyWorker(parent)
{
}

void MergeOtoOtoListModifyWorker::doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                                         OtoEntryList &secondSaveOtoList, const OptionContainer &options)
{
    Q_UNUSED(secondSaveOtoList)
    auto otherOtoLoaded = options.getOption("otherOtoLoaded").toBool();
    if (!otherOtoLoaded)
        throw ToolException(tr("The oto file to merge from has not been loaded."));
    auto otherOtoList = options.getOption("otherOtoList").value<OtoEntryList>();
    auto mergeStrtegy =
        (MergeOtoOptionWidget::MergeStrategy)options.getOption("mergeStrategy", MergeOtoOptionWidget::Replace).toInt();

    resultOtoList = srcOtoList;
    for (const auto &otherEntry : qAsConst(otherOtoList)) {
        auto it = std::ranges::find_if(
            resultOtoList, [&otherEntry](const OtoEntry &srcEntry) { return srcEntry.alias() == otherEntry.alias(); });
        if (it != resultOtoList.end()) {
            auto idx = std::distance(resultOtoList.begin(), it);
            if (mergeStrtegy == MergeOtoOptionWidget::Replace) {
                resultOtoList[idx] = otherEntry;
                continue;
            } else if (mergeStrtegy == MergeOtoOptionWidget::Skip)
                continue;
        }
        resultOtoList.append(otherEntry);
    }
}
