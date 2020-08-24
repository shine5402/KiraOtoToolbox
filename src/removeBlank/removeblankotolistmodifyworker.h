#ifndef REMOVEBLANKOTOLISTMODIFYWORKER_H
#define REMOVEBLANKOTOLISTMODIFYWORKER_H

#include "toolBase/otolistmodifyworker.h"


class RemoveBlankOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    RemoveBlankOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions &options) override;
};

#endif // REMOVEBLANKOTOLISTMODIFYWORKER_H
