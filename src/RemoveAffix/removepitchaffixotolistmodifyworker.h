#ifndef REMOVEPITCHAFFIXOTOLISTTASK_H
#define REMOVEPITCHAFFIXOTOLISTTASK_H

#include "../toolBase/otolistmodifyworker.h"

class RemovePitchAffixOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    explicit RemovePitchAffixOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions *options) override;
    QHash<int, QString> getRemovedPitchStringList() const;
private:
    QHash<int, QString> removedPitchStringList;
};

#endif // REMOVEPITCHAFFIXOTOLISTTASK_H
