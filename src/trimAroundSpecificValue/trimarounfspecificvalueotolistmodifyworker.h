#ifndef TRIMAROUNFSPECIFICVALUEOTOLISTMODIFYWORKER_H
#define TRIMAROUNFSPECIFICVALUEOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>
#include <QObject>

class TrimArounfSpecificValueOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE TrimArounfSpecificValueOtoListModifyWorker(QObject* parent = nullptr);
    void doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                OtoEntryList &secondSaveOtoList, const OptionContainer &options) override;
};

#endif // TRIMAROUNFSPECIFICVALUEOTOLISTMODIFYWORKER_H
