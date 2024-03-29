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
    Q_INVOKABLE explicit RemoveAffixOtoListModifyWorker(QObject* parent = nullptr);
    void doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
    RemoveSpecificAffixOtoListModifyWorker* getSpecificWorker() const;
    RemovePitchAffixOtoListModifyWorker* getPitchWorker() const;

private:
    RemoveSpecificAffixOtoListModifyWorker* specificWorker = nullptr;
    RemovePitchAffixOtoListModifyWorker* pitchWorker = nullptr;
};

#endif // REMOVEAFFIXOTOLISTTASK_H
