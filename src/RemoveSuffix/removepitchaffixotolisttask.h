#ifndef REMOVEPITCHAFFIXOTOLISTTASK_H
#define REMOVEPITCHAFFIXOTOLISTTASK_H

#include "../toolBase/otolisttask.h"

class RemovePitchAffixOtoListTask : public OtoListTask
{
    Q_OBJECT
public:
    explicit RemovePitchAffixOtoListTask(QObject* parent = nullptr);
    bool doTask(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions *options) override;
    QHash<int, QString> getRemovedPitchStringList() const;
private:
    QHash<int, QString> removedPitchStringList;
};

#endif // REMOVEPITCHAFFIXOTOLISTTASK_H
