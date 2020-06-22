#include "removeaffixotolisttask.h"
#include "removepitchaffixotolisttask.h"
#include "removespecificaffixotolisttask.h"

RemoveAffixOtoListTask::RemoveAffixOtoListTask(QObject* parent) : OtoListTask(parent)
{

}

bool RemoveAffixOtoListTask::doTask(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options)
{
    RemoveSpecificAffixOtoListTask specificTask;
    auto result = specificTask.doTask(srcOtoList, resultOtoList, secondSaveOtoList, options);
    RemovePitchAffixOtoListTask pitchTesk;
    result &= specificTask.doTask(srcOtoList, resultOtoList, secondSaveOtoList, options);
    return result;
}
