#include "setaliasotolistmodifyworker.h"

SetAliasOtoListModifyWorker::SetAliasOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}


bool SetAliasOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    resultOtoList = srcOtoList;

    //%s digit suffix
    QStringList digitSuffixList;
    for (int i = 0; i < srcOtoList.count(); ++i)
    {
        auto suffix = OtoEntryFunctions::getDigitSuffix(srcOtoList.at(i).alias());
        digitSuffixList.append(suffix);
    }

    //main logic
    QStringList workingAliasList;
    for (int i = 0; i < srcOtoList.count(); ++i)
    {
        auto currentAlias = options.getOption("renamingRule").toString();

        if (options.getOption("onlyForEmpty").toBool() && !srcOtoList.at(i).alias().isEmpty()){
             workingAliasList.append(srcOtoList.at(i).alias());
            continue;
        }

        //renaming rule, we will deal with %r later.
        currentAlias.replace("%s", digitSuffixList.at(i));
        auto shouldRemoveSuffix = options.getOption("renamingRule").toString().contains("%s");
        currentAlias.replace("%a", shouldRemoveSuffix ? OtoEntryFunctions::removeSuffix(srcOtoList.at(i).alias(), digitSuffixList.at(i)) : srcOtoList.at(i).alias());
        currentAlias.replace("%f", srcOtoList.at(i).fileName().remove(".wav"));

        //cut
        currentAlias.remove(0, options.getOption("cutHeadCount").toInt());
        currentAlias.remove(currentAlias.count() - options.getOption("cutTailCount").toInt(),
                            options.getOption("cutTailCount").toInt());

        //remove specific string
        if (options.getOption("strShouldRemoveIsRegex").toBool())
            currentAlias.remove(QRegExp(options.getOption("strShouldRemove").toString()));
        else
            currentAlias.remove(options.getOption("strShouldRemove").toString());
        workingAliasList.append(currentAlias);
    }

    //deal with %r
    QStringList &compareStringList = workingAliasList;

    QMultiHash<QString, int> compareStringMap;

    for (int i = 0; i < compareStringList.count(); ++i)
    {
        compareStringMap.insert(compareStringList.at(i), i);
    }

    QHash <int, QString> newAlias;
    for (const auto& key : compareStringMap.uniqueKeys())
    {
        auto values = compareStringMap.values(key);
        std::sort(values.begin(), values.end());

        for (int i = 0; i < values.count(); ++i)
        {
            auto currentID = values.at(i);
            newAlias.insert(currentID, compareStringList.at(currentID) +
                            (i > 0 ? QString::number(i + 1) : ""));
        }
    }

    for (int i = 0; i < srcOtoList.count(); ++i)
    {
        auto currentAlias = workingAliasList.at(i);
        currentAlias.replace("%r", newAlias.value(i, ""));
        resultOtoList[i].setAlias(currentAlias);
    }

    return true;
}
