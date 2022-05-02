#include "removeaffixotolistmodifyworker.h"
#include "removepitchaffixotolistmodifyworker.h"
#include "removespecificaffixotolistmodifyworker.h"

RemoveAffixOtoListModifyWorker::RemoveAffixOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{
    specificWorker = new RemoveSpecificAffixOtoListModifyWorker(this);
    pitchWorker = new RemovePitchAffixOtoListModifyWorker(this);
}

void RemoveAffixOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    OptionContainer newOptions(options);
    if (!options.getOption("removePitchAffix").toBool())
    {
        newOptions.setOption("removePitchPrefix", false);
        newOptions.setOption("removePitchSuffix", false);
    }

    OtoEntryList lastResult = srcOtoList;
    OtoEntryList currentResult;

    auto updateResult = [&](){
        lastResult = std::move(currentResult);
        currentResult = {};
    };

    specificWorker->doWork(lastResult, currentResult, secondSaveOtoList, newOptions);
    updateResult();
    pitchWorker->doWork(lastResult, currentResult, secondSaveOtoList, newOptions);

    resultOtoList = currentResult;
}

RemoveSpecificAffixOtoListModifyWorker* RemoveAffixOtoListModifyWorker::getSpecificWorker() const
{
    return specificWorker;
}

RemovePitchAffixOtoListModifyWorker* RemoveAffixOtoListModifyWorker::getPitchWorker() const
{
    return pitchWorker;
}

