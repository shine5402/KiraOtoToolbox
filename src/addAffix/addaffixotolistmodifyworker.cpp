#include "addaffixotolistmodifyworker.h"

AddAffixOtoListModifyWorker::AddAffixOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

bool AddAffixOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions& options)
{
    Q_UNUSED(secondSaveOtoList)
    resultOtoList = srcOtoList;

    auto prefix = options.getOption("prefix").toString();
    auto suffix = options.getOption("suffix").toString();

    for (auto& i : resultOtoList)
    {
        i.setAlias(prefix + i.alias() + suffix);
    }

    return true;
}
