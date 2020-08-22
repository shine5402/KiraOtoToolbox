#ifndef ORGNAIZEDUPLICATEOTOLISTMODIFYWORKER_H
#define ORGNAIZEDUPLICATEOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>


class OrgnaizeDuplicateOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    OrgnaizeDuplicateOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions *options) override;
};

#endif // ORGNAIZEDUPLICATEOTOLISTMODIFYWORKER_H
