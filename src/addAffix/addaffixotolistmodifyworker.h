#ifndef ADDAFFIXOTOLISTMODIFYWORKER_H
#define ADDAFFIXOTOLISTMODIFYWORKER_H
#include <toolBase/otolistmodifyworker.h>

#include <QObject>

class AddAffixOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    AddAffixOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions *options) override;
};

#endif // ADDAFFIXOTOLISTMODIFYWORKER_H
