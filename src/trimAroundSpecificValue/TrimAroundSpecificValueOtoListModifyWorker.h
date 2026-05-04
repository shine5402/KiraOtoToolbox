#ifndef TRIMAROUNDSPECIFICVALUEOTOLISTMODIFYWORKER_H
#define TRIMAROUNDSPECIFICVALUEOTOLISTMODIFYWORKER_H

#include <QObject>

#include "toolBase/OtoListModifyWorker.h"

class TrimAroundSpecificValueOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE TrimAroundSpecificValueOtoListModifyWorker(QObject *parent = nullptr);
    void doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList,
                const OptionContainer &options) override;
};

#endif // TRIMAROUNDSPECIFICVALUEOTOLISTMODIFYWORKER_H
