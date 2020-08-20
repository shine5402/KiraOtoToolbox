#ifndef REMOVEAFFIXOTOLISTTASK_H
#define REMOVEAFFIXOTOLISTTASK_H

#include <QObject>
#include "../toolBase/otolistmodifyworker.h"

class RemoveSpecificAffixOtoListTask;
class RemovePitchAffixOtoListTask;

class RemoveAffixOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    explicit RemoveAffixOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options) override;
    RemoveSpecificAffixOtoListTask* getSpecificTask() const;
    RemovePitchAffixOtoListTask* getPitchTask() const;

private:
    RemoveSpecificAffixOtoListTask* specificTask = nullptr;
    RemovePitchAffixOtoListTask* pitchTask = nullptr;
};

#endif // REMOVEAFFIXOTOLISTTASK_H
