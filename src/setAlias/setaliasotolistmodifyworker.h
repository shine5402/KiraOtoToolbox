#ifndef SETALIASOTOLISTMODIFYWORKER_H
#define SETALIASOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>

class SetAliasOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE SetAliasOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
};

#endif // SETALIASOTOLISTMODIFYWORKER_H
