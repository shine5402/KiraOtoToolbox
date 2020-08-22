#ifndef REMOVEDUPLICATEOTOLISTMODIFYWORKER_H
#define REMOVEDUPLICATEOTOLISTMODIFYWORKER_H
#include <toolBase/otolistmodifyworker.h>


class RemoveDuplicateOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    RemoveDuplicateOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions *options) override;
};

#endif // REMOVEDUPLICATEOTOLISTMODIFYWORKER_H
