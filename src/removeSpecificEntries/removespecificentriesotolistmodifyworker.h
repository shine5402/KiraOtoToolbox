#ifndef REMOVESPECIFICENTRIESOTOLISTMODIFYWORKER_H
#define REMOVESPECIFICENTRIESOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>

class RemoveSpecificEntriesOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit RemoveSpecificEntriesOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
};

#endif // REMOVESPECIFICENTRIESOTOLISTMODIFYWORKER_H
