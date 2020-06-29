#include "removeaffixotolisttask.h"
#include "removepitchaffixotolisttask.h"
#include "removespecificaffixotolisttask.h"

RemoveAffixOtoListTask::RemoveAffixOtoListTask(QObject* parent) : OtoListTask(parent)
{
    specificTask = new RemoveSpecificAffixOtoListTask(this);
    pitchTask = new RemovePitchAffixOtoListTask(this);
}

bool RemoveAffixOtoListTask::doTask(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options)
{
    auto result = specificTask->doTask(srcOtoList, resultOtoList, secondSaveOtoList, options);
    result &= pitchTask->doTask(srcOtoList, resultOtoList, secondSaveOtoList, options);
    return result;
}

