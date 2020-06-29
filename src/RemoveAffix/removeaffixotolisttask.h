#ifndef REMOVEAFFIXOTOLISTTASK_H
#define REMOVEAFFIXOTOLISTTASK_H

#include <QObject>
#include "../toolBase/otolisttask.h"

class RemoveSpecificAffixOtoListTask;
class RemovePitchAffixOtoListTask;

class RemoveAffixOtoListTask : public OtoListTask
{
    Q_OBJECT
public:
    explicit RemoveAffixOtoListTask(QObject* parent = nullptr);
    bool doTask(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options) override;
    RemoveSpecificAffixOtoListTask* getSpecificTask() const;
    RemovePitchAffixOtoListTask* getPitchTask() const;

private:
    RemoveSpecificAffixOtoListTask* specificTask = nullptr;
    RemovePitchAffixOtoListTask* pitchTask = nullptr;
};

#endif // REMOVEAFFIXOTOLISTTASK_H
