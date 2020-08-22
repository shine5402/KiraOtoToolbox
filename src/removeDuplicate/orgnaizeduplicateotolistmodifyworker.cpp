#include "orgnaizeduplicateotolistmodifyworker.h"

OrgnaizeDuplicateOtoListModifyWorker::OrgnaizeDuplicateOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

bool OrgnaizeDuplicateOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options)
{
    //整理重复项
    //if (options->getOption("shouldOrganize").toBool()){
        /*
         * 要做的事：重整重复项数字顺序，添加原后缀。
         */
    QStringList compareStringList;
    for (int i = 0; i < srcOtoList.count(); ++i)
    {
        compareStringList.append(srcOtoList.at(i).alias());
    }
    QMultiHash<QString, int> compareStringMap;

    for (int i = 0; i < compareStringList.count(); ++i)
    {
        compareStringMap.insertMulti(compareStringList.at(i), i);
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
                                (i > 0 ? QString::number((options->getOption("organizeStartFrom1").toBool() ? i : i + 1)) : ""));
                //FIXME: 在外层Adapter考虑被去除的情况
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
