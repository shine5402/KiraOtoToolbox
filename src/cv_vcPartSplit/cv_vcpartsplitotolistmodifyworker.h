#ifndef CV_VCPARTSPLITOTOLISTMODIFYWORKER_H
#define CV_VCPARTSPLITOTOLISTMODIFYWORKER_H

#include "toolBase/otolistmodifyworker.h"

class CV_VCPartSplitOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit CV_VCPartSplitOtoListModifyWorker(QObject *parent = nullptr);
    void doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
};

#endif // CV_VCPARTSPLITOTOLISTMODIFYWORKER_H
