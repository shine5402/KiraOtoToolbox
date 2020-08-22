#ifndef REMOVESPECIFICAFFIXOTOLISTTASK_H
#define REMOVESPECIFICAFFIXOTOLISTTASK_H

#include "../toolBase/otolistmodifyworker.h"
#include "removedstringinfo.h"

class RemoveSpecificAffixOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    explicit RemoveSpecificAffixOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions *options) override;

    QVector<RemovedStringInfo> getRemovedStringInfos() const;

private:
    QVector<RemovedStringInfo> removedStringInfos;
};

#endif // REMOVESPECIFICAFFIXOTOLISTTASK_H
