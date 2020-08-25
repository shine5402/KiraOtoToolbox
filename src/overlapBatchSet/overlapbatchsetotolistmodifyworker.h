#ifndef OVERLAPBATCHSETOTOLISTMODIFYWORKER_H
#define OVERLAPBATCHSETOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>

class OverlapBatchSetOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE OverlapBatchSetOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions& options) override;
};

#endif // OVERLAPBATCHSETOTOLISTMODIFYWORKER_H
