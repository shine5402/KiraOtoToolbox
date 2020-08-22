#ifndef REMOVEAFFIXOTOLISTTASK_H
#define REMOVEAFFIXOTOLISTTASK_H

#include <QObject>
#include "../toolBase/otolistmodifyworker.h"

class RemoveSpecificAffixOtoListModifyWorker;
class RemovePitchAffixOtoListModifyWorker;

class RemoveAffixOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    explicit RemoveAffixOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions& options) override;
    RemoveSpecificAffixOtoListModifyWorker* getSpecificWorker() const;
    RemovePitchAffixOtoListModifyWorker* getPitchWorker() const;

private:
    RemoveSpecificAffixOtoListModifyWorker* specificWorker = nullptr;
    RemovePitchAffixOtoListModifyWorker* pitchWorker = nullptr;
};

#endif // REMOVEAFFIXOTOLISTTASK_H
