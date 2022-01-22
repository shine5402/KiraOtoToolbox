#ifndef TEMPOTRANSFORMOTOLISTMODIFYWORKER_H
#define TEMPOTRANSFORMOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>

class TempoTransformOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TempoTransformOtoListModifyWorker(QObject *parent = nullptr);
    bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
};

#endif // TEMPOTRANSFORMOTOLISTMODIFYWORKER_H
