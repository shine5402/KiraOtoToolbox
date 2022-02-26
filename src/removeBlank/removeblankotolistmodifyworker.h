#ifndef REMOVEBLANKOTOLISTMODIFYWORKER_H
#define REMOVEBLANKOTOLISTMODIFYWORKER_H

#include "toolBase/otolistmodifyworker.h"


class RemoveBlankOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE RemoveBlankOtoListModifyWorker(QObject* parent = nullptr);
    void doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                OtoEntryList &secondSaveOtoList, const OptionContainer &options) override;
};

#endif // REMOVEBLANKOTOLISTMODIFYWORKER_H
