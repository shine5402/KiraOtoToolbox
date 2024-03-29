#include "addaffixotolistmodifyworker.h"

AddAffixOtoListModifyWorker::AddAffixOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

void AddAffixOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                         OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)
    resultOtoList = srcOtoList;

    auto prefix = options.getOption("prefix").toString();
    auto suffix = options.getOption("suffix").toString();

    for (auto& i : resultOtoList)
    {
        i.setAlias(prefix + i.alias() + suffix);
    }
}
