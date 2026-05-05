#ifndef NOTDOANYTHINGOTOLISTMODIFYWORKER_H
#define NOTDOANYTHINGOTOLISTMODIFYWORKER_H

#include "../toolBase/OtoListModifyWorker.h"

class NotDoAnythingOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit NotDoAnythingOtoListModifyWorker(QObject *parent = nullptr);
    void doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList,
                const OptionContainer &options) override;
};

#endif // NOTDOANYTHINGOTOLISTMODIFYWORKER_H
