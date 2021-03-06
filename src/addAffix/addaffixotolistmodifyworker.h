#ifndef ADDAFFIXOTOLISTMODIFYWORKER_H
#define ADDAFFIXOTOLISTMODIFYWORKER_H
#include <toolBase/otolistmodifyworker.h>

#include <QObject>

class AddAffixOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE AddAffixOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const OptionContainer& options) override;
};

#endif // ADDAFFIXOTOLISTMODIFYWORKER_H
