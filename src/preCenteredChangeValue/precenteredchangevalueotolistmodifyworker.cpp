#include "precenteredchangevalueotolistmodifyworker.h"

PreCenteredChangeValueOtoListModifyWorker::PreCenteredChangeValueOtoListModifyWorker(QObject *parent)
    : OtoListModifyWorker{parent}
{

}

void PreCenteredChangeValueOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                       OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    auto changeConstField = options.getOption("changeConstField").toBool();
    auto constField = options.getOption("constField").toDouble();
    auto changePreutterance = options.getOption("changePreutterance").toBool();
    auto preutterance = options.getOption("preutterance").toDouble();
    auto changeOverlap = options.getOption("changeOverlap").toBool();
    auto overlap = options.getOption("overlap").toDouble();
    auto changeRight = options.getOption("changeRight").toBool();
    auto right = options.getOption("right").toDouble();
    resultOtoList = {};
    for (const auto& entry : srcOtoList){
        auto newEntry = entry;
        if (changePreutterance){
            auto preDiff = entry.preUtterance() - preutterance;
            auto newLeft = preDiff + entry.left();
            newEntry.setLeft(newLeft >= 0 ? newLeft : entry.left());
            newEntry.setPreUtterance(newLeft >= 0 ? preutterance : entry.preUtterance());
            //To ensure new const field still have same relative position to pre
            newEntry.setConsonant(entry.consonant() - preDiff);
        }
        if (changeConstField)
            newEntry.setConsonant(constField);
        if (changeOverlap)
            newEntry.setOverlap(overlap);
        if (changeRight)
            newEntry.setRight(right);
        resultOtoList.append(newEntry);
    }
}
