#include "removespecificaffixotolistmodifyworker.h"

RemoveSpecificAffixOtoListModifyWorker::RemoveSpecificAffixOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

void RemoveSpecificAffixOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                    OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList);
    resultOtoList = srcOtoList;

    removedStringInfos.clear();

    QStringList affixList{};
    std::function<decltype (OtoEntryFunctions::removePrefix)> removeFunc;
    std::function<bool(const OtoEntry&, const QString&)> compareFunc;

    auto func = [&](RemovedStringInfo::AffixType type){for (int i = 0; i < srcOtoList.count(); ++i)
    {
        auto& currentOto = resultOtoList[i];
        for (const auto& currentAffix : affixList)
        {
            if (compareFunc(currentOto, currentAffix))
            {
                auto result = removeFunc(currentOto.alias(), currentAffix, Qt::CaseSensitive, nullptr);
                currentOto.setAlias(result);
                removedStringInfos.append(RemovedStringInfo(type, i, currentAffix));
            }
        }
    }
    };

    Q_ASSERT(options.getOption("removePrefix").toBool() || options.getOption("removeSuffix").toBool());

    if (options.getOption("removePrefix").toBool()){
        removeFunc = OtoEntryFunctions::removePrefix;
        affixList = options.getOption("prefixList").toStringList();
        compareFunc = [](const OtoEntry& oto, const QString& prefix) -> bool {
            return oto.alias().startsWith(prefix);
        };
        func(RemovedStringInfo::Prefix);
    }

    if (options.getOption("removeSuffix").toBool()){
        removeFunc = OtoEntryFunctions::removeSuffix;
        affixList = options.getOption("suffixList").toStringList();
        compareFunc = [](const OtoEntry& oto, const QString& suffix) -> bool {
            return oto.alias().endsWith(suffix);
        };
        func(RemovedStringInfo::Suffix);
    }
}

QVector<RemovedStringInfo> RemoveSpecificAffixOtoListModifyWorker::getRemovedStringInfos() const
{
    return removedStringInfos;
}
