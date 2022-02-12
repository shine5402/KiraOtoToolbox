#ifndef REMOVEDUPLICATEOTOLISTMODIFYWORKER_H
#define REMOVEDUPLICATEOTOLISTMODIFYWORKER_H
#include <toolBase/otolistmodifyworker.h>


class RemoveDuplicateOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE RemoveDuplicateOtoListModifyWorker(QObject* parent = nullptr);
    void doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                OtoEntryList &secondSaveOtoList, const OptionContainer& options) override;

    QList<int> getRemovedIDs() const;

private:
    QList<int> removedIDs;
};

#endif // REMOVEDUPLICATEOTOLISTMODIFYWORKER_H
