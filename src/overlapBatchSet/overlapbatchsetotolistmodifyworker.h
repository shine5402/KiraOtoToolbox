#ifndef OVERLAPBATCHSETOTOLISTMODIFYWORKER_H
#define OVERLAPBATCHSETOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>

class OverlapBatchSetOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE OverlapBatchSetOtoListModifyWorker(QObject* parent = nullptr);
    void doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                OtoEntryList &secondSaveOtoList, const OptionContainer& options) override;
};

#endif // OVERLAPBATCHSETOTOLISTMODIFYWORKER_H
