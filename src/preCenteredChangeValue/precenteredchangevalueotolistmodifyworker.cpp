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
        newEntry.setLeft(entry.preUtterance() - preutterance + entry.left());
        newEntry.setPreUtterance(preutterance);
        newEntry.setConsonant(constField);
        newEntry.setOverlap(overlap);
        newEntry.setRight(right);
        resultOtoList.append(newEntry);
    }

    //TODO:check for negative left as they are invalid, or give a ignore/bound to zero option
    return true;
}
