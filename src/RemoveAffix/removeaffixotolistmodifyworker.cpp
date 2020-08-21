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
    auto result = specificWorker->doWork(srcOtoList, resultOtoList, secondSaveOtoList, options);
    result |= pitchWorker->doWork(srcOtoList, resultOtoList, secondSaveOtoList, options);
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

