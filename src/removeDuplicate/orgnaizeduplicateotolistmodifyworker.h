#ifndef ORGNAIZEDUPLICATEOTOLISTMODIFYWORKER_H
#define ORGNAIZEDUPLICATEOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>


class OrgnaizeDuplicateOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE OrgnaizeDuplicateOtoListModifyWorker(QObject* parent = nullptr);
    void doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                OtoEntryList &secondSaveOtoList, const OptionContainer& options) override;
};

#endif // ORGNAIZEDUPLICATEOTOLISTMODIFYWORKER_H
