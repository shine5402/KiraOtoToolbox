#ifndef CV_VCPARTSPLITOTOLISTMODIFYWORKER_H
#define CV_VCPARTSPLITOTOLISTMODIFYWORKER_H

#include "toolBase/otolistmodifyworker.h"

class CV_VCPartSplitOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    explicit CV_VCPartSplitOtoListModifyWorker(QObject *parent = nullptr);

    // OtoListModifyWorker interface
public:
    bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
};

#endif // CV_VCPARTSPLITOTOLISTMODIFYWORKER_H
