#ifndef REMOVESPECIFICAFFIXOTOLISTTASK_H
#define REMOVESPECIFICAFFIXOTOLISTTASK_H

#include <QObject>
#include "../toolBase/otolisttask.h"

class RemoveSpecificAffixOtoListTask : public OtoListTask
{
    Q_OBJECT
public:
    explicit RemoveSpecificAffixOtoListTask(QObject* parent = nullptr);
    bool doTask(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions *options) override;
    QHash<int, QString> getRemovedSpecificPrefixMap() const;
    QHash<int, QString> getRemovedSpecificSuffixMap() const;

private:
    QHash<int, QString> removedSpecificPrefixMap{};
    QHash<int, QString> removedSpecificSuffixMap{};
};

#endif // REMOVESPECIFICAFFIXOTOLISTTASK_H
