#ifndef ORGANIZEDUPLICATEOTOLISTMODIFYWORKER_H
#define ORGANIZEDUPLICATEOTOLISTMODIFYWORKER_H

#include "toolBase/OtoListModifyWorker.h"


class OrganizeDuplicateOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE OrganizeDuplicateOtoListModifyWorker(QObject* parent = nullptr);
    void doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                OtoEntryList &secondSaveOtoList, const OptionContainer& options) override;
};

#endif // ORGANIZEDUPLICATEOTOLISTMODIFYWORKER_H
