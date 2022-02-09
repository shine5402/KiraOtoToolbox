#include "orgnaizeduplicateotolistmodifyworker.h"

OrgnaizeDuplicateOtoListModifyWorker::OrgnaizeDuplicateOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

void OrgnaizeDuplicateOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                  OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
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
        auto suffix = OtoEntryFunctions::getDigitSuffix(compareStringList.at(i), nullptr, options.getOption("considerNegativeSuffix").toBool());
        digitSuffixList.append(suffix);
        compareStringList.replace(i, OtoEntryFunctions::removeSuffix(compareStringList.at(i), suffix));
    }

    QMultiHash<QString, int> compareStringMap;//alias, rawID

    for (int i = 0; i < compareStringList.count(); ++i)
    {
        compareStringMap.insert(compareStringList.at(i), i);
    }
    QHash <int, QString> newAlias;
    auto stringListUnique = compareStringMap.uniqueKeys();
    for (const auto& key : std::as_const(stringListUnique))
    {
        auto values = compareStringMap.values(key);//rawIDs
        std::sort(values.begin(), values.end(), [&](int lhs, int rhs){
            if (options.getOption("respectOriginalNumberOrder").toBool())
            {
                bool lhs_ok = false, rhs_ok = false;
                auto lhs_original = digitSuffixList.at(lhs).toInt(&lhs_ok);
                auto rhs_original = digitSuffixList.at(rhs).toInt(&rhs_ok);
                if (!lhs_ok)
                    return false;
                if (!rhs_ok)
                    return true;
                return lhs_original < rhs_original;
            }
            return lhs < rhs;
        });

        for (int i = 0; i < values.count(); ++i)
        {
            auto currentID = values.at(i);
            newAlias.insert(currentID, compareStringList.at(currentID) +
                            (i > 0 ? QString::number((options.getOption("organizeStartFrom1").toBool() ? i : i + 1)) : ""));
        }
    }
    for (auto it = newAlias.keyBegin(); it != newAlias.keyEnd(); ++it)
    {
        auto& currentID = *it;
        auto currentEntry = resultOtoList.at(currentID);
        currentEntry.setAlias(newAlias.value(currentID));
        resultOtoList.replace(currentID, currentEntry);
    }
}
