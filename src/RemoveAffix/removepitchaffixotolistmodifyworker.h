#ifndef REMOVEPITCHAFFIXOTOLISTTASK_H
#define REMOVEPITCHAFFIXOTOLISTTASK_H

#include "../toolBase/otolistmodifyworker.h"
#include "removedstringinfo.h"
//TODO:使用类来说明被删除情况

class RemovePitchAffixOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    explicit RemovePitchAffixOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions *options) override;
    QVector<RemovedStringInfo> getRemovedStringInfos() const;

private:
    QVector<RemovedStringInfo> removedStringInfos;
};

#endif // REMOVEPITCHAFFIXOTOLISTTASK_H
