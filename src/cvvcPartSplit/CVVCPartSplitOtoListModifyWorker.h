#ifndef CV_VCPARTSPLITOTOLISTMODIFYWORKER_H
#define CV_VCPARTSPLITOTOLISTMODIFYWORKER_H

#include "toolBase/OtoListModifyWorker.h"

class CVVCPartSplitOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit CVVCPartSplitOtoListModifyWorker(QObject *parent = nullptr);
    void doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;

    bool needConfirm() const override;
    QVector<ConfirmMsg> getConfirmMsgs() const override;
private:
    //dry-run states, for confirm
    bool VCExtractedToNewFile = false;
    OtoEntryList VCList;
};

#endif // CV_VCPARTSPLITOTOLISTMODIFYWORKER_H
