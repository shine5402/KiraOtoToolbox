#include "removeaffixotolistmodifyworker.h"
#include "removepitchaffixotolistmodifyworker.h"
#include "removespecificaffixotolistmodifyworker.h"

RemoveAffixOtoListModifyWorker::RemoveAffixOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{
    specificWorker = new RemoveSpecificAffixOtoListModifyWorker(this);
    pitchWorker = new RemovePitchAffixOtoListModifyWorker(this);
}

bool RemoveAffixOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    OptionContainer newOptions(options);
    if (!options.getOption("removePitchAffix").toBool())
    {
        newOptions.setOption("removePitchPrefix", false);
        newOptions.setOption("removePitchSuffix", false);
    }

    OtoEntryList lastResult = srcOtoList;
    OtoEntryList currentResult;
    bool success = false;

    auto updateResult = [&](){
        lastResult = std::move(currentResult);
        currentResult = {};
    };

    success = specificWorker->doWork(lastResult, currentResult, secondSaveOtoList, newOptions);
    updateResult();
    success |= pitchWorker->doWork(lastResult, currentResult, secondSaveOtoList, newOptions);

    resultOtoList = currentResult;

    return success;
}

RemoveSpecificAffixOtoListModifyWorker* RemoveAffixOtoListModifyWorker::getSpecificWorker() const
{
    return specificWorker;
}

RemovePitchAffixOtoListModifyWorker* RemoveAffixOtoListModifyWorker::getPitchWorker() const
{
    return pitchWorker;
}

