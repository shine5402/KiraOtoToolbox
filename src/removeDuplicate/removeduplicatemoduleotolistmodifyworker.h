#ifndef REMOVEDUPLICATEMODULEOTOLISTMODIFYWORKER_H
#define REMOVEDUPLICATEMODULEOTOLISTMODIFYWORKER_H

#include "toolBase/otolistmodifyworker.h"

class RemoveDuplicateModuleOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE RemoveDuplicateModuleOtoListModifyWorker(QObject* parent = nullptr);
    void doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                OtoEntryList &secondSaveOtoList, const OptionContainer &options) override;

private:
    // for confirm
    OtoEntryList organizeResult;
    OtoEntryList toBeRemovedOtoList;
    OtoEntryList srcOtoList;
    int precision;

    // OtoListModifyWorker interface
public:
    bool needConfirm() const override;
    QVector<ConfirmMsg> getConfirmMsgs() const override;
};

#endif // REMOVEDUPLICATEMODULEOTOLISTMODIFYWORKER_H
