#ifndef ADDAFFIXOTOLISTMODIFYWORKER_H
#define ADDAFFIXOTOLISTMODIFYWORKER_H
#include <QObject>

#include "toolBase/OtoListModifyWorker.h"

class AddAffixOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE AddAffixOtoListModifyWorker(QObject *parent = nullptr);
    void doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList,
                const OptionContainer &options) override;
};

#endif // ADDAFFIXOTOLISTMODIFYWORKER_H
