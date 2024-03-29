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
    bool needConfirm() const override;
    QVector<ConfirmMsg> getConfirmMsgs() const override;
    bool isConfirmDialogAccepted(int msgTypeId, int dialogResult) const override;
    void commit() override;

private:
    QVector<std::shared_ptr<OtoListModifyWorker>> needConfirmWorkers;
};

#endif // CHAINOTOLISTMODIFYWORKER_H
