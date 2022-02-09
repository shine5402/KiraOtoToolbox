#ifndef CHAINOTOLISTMODIFYWORKER_H
#define CHAINOTOLISTMODIFYWORKER_H

#include "toolBase/otolistmodifyworker.h"

class ChainOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE ChainOtoListModifyWorker(QObject* parent = nullptr);
    void doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                OtoEntryList &secondSaveOtoList, const OptionContainer &options) override;
};

#endif // CHAINOTOLISTMODIFYWORKER_H
