#ifndef REMOVEDUPLICATEMODULEOTOLISTMODIFYWORKER_H
#define REMOVEDUPLICATEMODULEOTOLISTMODIFYWORKER_H

#include "toolBase/otolistmodifyworker.h"

class RemoveDuplicateModuleOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE RemoveDuplicateModuleOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions &options) override;
    OtoEntryList getOrganizeResult() const;

private:
    OtoEntryList organizeResult;
};

#endif // REMOVEDUPLICATEMODULEOTOLISTMODIFYWORKER_H
