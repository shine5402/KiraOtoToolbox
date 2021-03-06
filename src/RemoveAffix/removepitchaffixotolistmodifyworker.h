#ifndef REMOVEPITCHAFFIXOTOLISTTASK_H
#define REMOVEPITCHAFFIXOTOLISTTASK_H

#include "../toolBase/otolistmodifyworker.h"
#include "removedstringinfo.h"

class RemovePitchAffixOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit RemovePitchAffixOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const OptionContainer& options) override;
    QVector<RemovedStringInfo> getRemovedStringInfos() const;

private:
    QVector<RemovedStringInfo> removedStringInfos;
};

#endif // REMOVEPITCHAFFIXOTOLISTTASK_H
