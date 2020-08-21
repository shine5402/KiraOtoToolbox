#include "removeaffixotolistmodifyworker.h"
#include "removepitchaffixotolistmodifyworker.h"
#include "removespecificaffixotolistmodifyworker.h"

RemoveAffixOtoListModifyWorker::RemoveAffixOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{
    specificWorker = new RemoveSpecificAffixOtoListModifyWorker(this);
    pitchWorker = new RemovePitchAffixOtoListModifyWorker(this);
}

bool RemoveAffixOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options)
{
    ToolOptions newOptions(*options);
    if (!options->getOption("removePitchAffix").toBool())
    {
        newOptions.setOption("removePitchPrefix", false);
        newOptions.setOption("removePitchSuffix", false);
    }

    auto result = specificWorker->doWork(srcOtoList, resultOtoList, secondSaveOtoList, &newOptions);
    result |= pitchWorker->doWork(srcOtoList, resultOtoList, secondSaveOtoList, &newOptions);
    return result;
}

RemoveSpecificAffixOtoListModifyWorker* RemoveAffixOtoListModifyWorker::getSpecificWorker() const
{
    return specificWorker;
}

RemovePitchAffixOtoListModifyWorker* RemoveAffixOtoListModifyWorker::getPitchWorker() const
{
    return pitchWorker;
}

