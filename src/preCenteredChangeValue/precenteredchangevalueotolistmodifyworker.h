#ifndef PRECENTEREDCHANGEVALUEOTOLISTMODIFYWORKER_H
#define PRECENTEREDCHANGEVALUEOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>

class PreCenteredChangeValueOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit PreCenteredChangeValueOtoListModifyWorker(QObject *parent = nullptr);
    void doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
};

#endif // PRECENTEREDCHANGEVALUEOTOLISTMODIFYWORKER_H
