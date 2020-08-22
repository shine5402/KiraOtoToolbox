#ifndef OVERLAPBATCHSETOTOLISTMODIFYWORKER_H
#define OVERLAPBATCHSETOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>

class OverlapBatchSetOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    OverlapBatchSetOtoListModifyWorker(QObject* parent);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions *options) override;
};

#endif // OVERLAPBATCHSETOTOLISTMODIFYWORKER_H
