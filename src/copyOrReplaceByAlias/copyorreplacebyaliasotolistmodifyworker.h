#ifndef COPYORREPLACEBYALIASOTOLISTMODIFYWORKER_H
#define COPYORREPLACEBYALIASOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>

class CopyOrReplaceByAliasOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit CopyOrReplaceByAliasOtoListModifyWorker(QObject* parent = nullptr);
    void doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
};

#endif // COPYORREPLACEBYALIASOTOLISTMODIFYWORKER_H
