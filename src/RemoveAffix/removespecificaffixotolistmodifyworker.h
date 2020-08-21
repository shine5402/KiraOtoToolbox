#ifndef REMOVESPECIFICAFFIXOTOLISTTASK_H
#define REMOVESPECIFICAFFIXOTOLISTTASK_H

#include <QObject>
#include "../toolBase/otolistmodifyworker.h"

class RemoveSpecificAffixOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    explicit RemoveSpecificAffixOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions *options) override;
    QHash<int, QString> getRemovedSpecificPrefixMap() const;
    QHash<int, QString> getRemovedSpecificSuffixMap() const;

private:
    QHash<int, QString> removedSpecificPrefixMap{};
    QHash<int, QString> removedSpecificSuffixMap{};
};

#endif // REMOVESPECIFICAFFIXOTOLISTTASK_H
