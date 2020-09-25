#include "orgnaizeduplicateotolistmodifyworker.h"

OrgnaizeDuplicateOtoListModifyWorker::OrgnaizeDuplicateOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

bool OrgnaizeDuplicateOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions& options)
{
    //整理重复项
    Q_UNUSED(secondSaveOtoList)
    resultOtoList = srcOtoList;
    QStringList compareStringList;
    for (int i = 0; i < srcOtoList.count(); ++i)
    {
        compareStringList.append(srcOtoList.at(i).alias());
    }

    QStringList digitSuffixList;
    for (int i = 0; i < srcOtoList.count(); ++i)
    {
        auto suffix = OtoEntryFunctions::getDigitSuffix(compareStringList.at(i));
        digitSuffixList.append(suffix);
        compareStringList.replace(i, OtoEntryFunctions::removeSuffix(compareStringList.at(i), suffix));
    }

    QMultiHash<QString, int> compareStringMap;

    for (int i = 0; i < compareStringList.count(); ++i)
    {
        compareStringMap.insert(compareStringList.at(i), i);
    }
        QHash <int, QString> newAlias;
        for (auto key : compareStringMap.uniqueKeys())
        {
            auto values = compareStringMap.values(key);
            std::sort(values.begin(), values.end());

            for (int i = 0; i < values.count(); ++i)
            {
                auto currentID = values.at(i);
                newAlias.insert(currentID, compareStringList.at(currentID) +
                                (i > 0 ? QString::number((options.getOption("organizeStartFrom1").toBool() ? i : i + 1)) : ""));
            }
        }
        for (auto currentID : newAlias.keys())
        {
            auto currentEntry = resultOtoList.at(currentID);
            currentEntry.setAlias(newAlias.value(currentID));
            resultOtoList.replace(currentID, currentEntry);
        }
        return true;
}
