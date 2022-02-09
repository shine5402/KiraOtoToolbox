#include "removeduplicateotolistmodifyworker.h"

RemoveDuplicateOtoListModifyWorker::RemoveDuplicateOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

void RemoveDuplicateOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    resultOtoList = srcOtoList;
    QStringList compareStringList;
    for (int i = 0; i < srcOtoList.count(); ++i)
    {
        compareStringList.append(srcOtoList.at(i).alias());
    }

    QStringList digitSuffixList;
    for (int i = 0; i < srcOtoList.count(); ++i)
    {
        auto suffix = OtoEntryFunctions::getDigitSuffix(compareStringList.at(i), nullptr, options.getOption("considerNegativeSuffix").toBool());
        digitSuffixList.append(suffix);
        compareStringList.replace(i, OtoEntryFunctions::removeSuffix(compareStringList.at(i), suffix));
    }

    QMultiHash<QString, int> compareStringMap;

    for (int i = 0; i < compareStringList.count(); ++i)
    {
        compareStringMap.insert(compareStringList.at(i), i);
    }

    if (options.getOption("maxDuplicateCount").toInt() != 0) {

        removedIDs.clear();
        auto uniqueKeys = compareStringMap.uniqueKeys();
        for (const auto &key : std::as_const(uniqueKeys))
        {
            if (compareStringMap.count(key) > options.getOption("maxDuplicateCount").toInt())
            {
                auto values = compareStringMap.values(key);
                std::sort(values.begin(), values.end());
                removedIDs.append(values.mid(options.getOption("maxDuplicateCount").toInt()));
            }
        }
        std::sort(removedIDs.begin(), removedIDs.end());
        OtoEntryList toBeRemovedOtoList;
        for (auto i : std::as_const(removedIDs))
        {
            toBeRemovedOtoList.append(resultOtoList.at(i));
        }

        secondSaveOtoList = toBeRemovedOtoList;

        for (const auto &i : std::as_const(toBeRemovedOtoList)){
            resultOtoList.removeOne(i);
        }
    }
}

QList<int> RemoveDuplicateOtoListModifyWorker::getRemovedIDs() const
{
    return removedIDs;
}
