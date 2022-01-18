#include "precenteredchangevalueotolistmodifyworker.h"

PreCenteredChangeValueOtoListModifyWorker::PreCenteredChangeValueOtoListModifyWorker(QObject *parent)
    : OtoListModifyWorker{parent}
{

}

bool PreCenteredChangeValueOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                       OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    auto constField = options.getOption("constField").toDouble();
    auto preutterance = options.getOption("preutterance").toDouble();
    auto overlap = options.getOption("overlap").toDouble();
    auto right = options.getOption("right").toDouble();
    resultOtoList = {};
    for (const auto& entry : srcOtoList){
        auto newEntry = entry;
        auto newLeft = entry.preUtterance() - preutterance + entry.left();
        newEntry.setLeft(newLeft >= 0 ? newLeft : entry.left());
        newEntry.setPreUtterance(newLeft >= 0 ? preutterance : entry.preUtterance());
        newEntry.setConsonant(constField);
        newEntry.setOverlap(overlap);
        newEntry.setRight(right);
        resultOtoList.append(newEntry);
    }

    return true;
}
