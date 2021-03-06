#ifndef REMOVESPECIFICAFFIXOTOLISTTASK_H
#define REMOVESPECIFICAFFIXOTOLISTTASK_H

#include "../toolBase/otolistmodifyworker.h"
#include "removedstringinfo.h"

class RemoveSpecificAffixOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit RemoveSpecificAffixOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const OptionContainer& options) override;

    QVector<RemovedStringInfo> getRemovedStringInfos() const;

private:
    QVector<RemovedStringInfo> removedStringInfos;
};

#endif // REMOVESPECIFICAFFIXOTOLISTTASK_H
