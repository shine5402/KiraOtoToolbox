#ifndef MERGEOTOOTOLISTMODIFYWORKER_H
#define MERGEOTOOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>

class MergeOtoOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MergeOtoOtoListModifyWorker(QObject *parent = nullptr);
    bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList,
                                   const OptionContainer& options) override;
};

#endif // MERGEOTOOTOLISTMODIFYWORKER_H
