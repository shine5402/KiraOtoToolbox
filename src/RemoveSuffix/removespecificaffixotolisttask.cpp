#include "removespecificaffixotolisttask.h"

RemoveSpecificAffixOtoListTask::RemoveSpecificAffixOtoListTask(QObject* parent) : OtoListTask(parent)
{

}

bool RemoveSpecificAffixOtoListTask::doTask(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options)
{
    Q_UNUSED(secondSaveOtoList);
    resultOtoList = srcOtoList;

    removedSpecificPrefixMap.clear();
    removedSpecificSuffixMap.clear();

    QStringList affixList{};
    std::function<decltype (OtoEntryFunctions::removePrefix)> removeFunc;
    std::function<bool(const OtoEntry&, const QString&)> compareFunc;
    QHash<int, QString>* removedMap = nullptr;

    auto func = [&](){for (int i = 0; i < srcOtoList.count(); ++i)
    {
        auto& currentOto = resultOtoList[i];
        for (const auto& currentAffix : affixList)
        {
            if (compareFunc(currentOto, currentAffix))
            {
                auto result = removeFunc(currentOto.alias(), currentAffix, Qt::CaseSensitive, nullptr);
                currentOto.setAlias(result);
                removedMap->insert(i, currentAffix);
            }
        }
    }
    };

    if (options->getOption("removePrefix").toBool()){
        removeFunc = OtoEntryFunctions::removePrefix;
        affixList = options->getOption("prefixList").toStringList();
        removedMap = &removedSpecificPrefixMap;
        compareFunc = [](const OtoEntry& oto, const QString& prefix) -> bool {
            return oto.alias().startsWith(prefix);
        };
        func();
    }

    if (options->getOption("removeSuffix").toBool()){
        removeFunc = OtoEntryFunctions::removeSuffix;
        affixList = options->getOption("suffixList").toStringList();
        removedMap = &removedSpecificSuffixMap;
        compareFunc = [](const OtoEntry& oto, const QString& suffix) -> bool {
            return oto.alias().endsWith(suffix);
        };
        func();
    }

    return removeFunc.operator bool();
}

QHash<int, QString> RemoveSpecificAffixOtoListTask::getRemovedSpecificPrefixMap() const
{
    return removedSpecificPrefixMap;
}

QHash<int, QString> RemoveSpecificAffixOtoListTask::getRemovedSpecificSuffixMap() const
{
    return removedSpecificSuffixMap;
}
