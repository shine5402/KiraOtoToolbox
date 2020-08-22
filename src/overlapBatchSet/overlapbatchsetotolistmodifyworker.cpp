#include "overlapbatchsetotolistmodifyworker.h"

OverlapBatchSetOtoListModifyWorker::OverlapBatchSetOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

bool OverlapBatchSetOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const ToolOptions* options)
{
    Q_UNUSED(secondSaveOtoList)
    resultOtoList = srcOtoList;

    QVector<int> matched;
    //匹配开头并设置为指定数值
    if (options->getOption("ifSetOverlapStartWith").toBool())
    {
        for (int i = 0; i < resultOtoList.count(); ++i)
        {
            auto entry = resultOtoList.at(i);
            for (auto s : options->getOption("startWithPatternList").toStringList())
            {
                if (entry.alias().startsWith(s) || (options->getOption("ifMatchStartOto").toBool() && entry.alias().startsWith("- " + s)))
                {
                    entry.setOverlap(options->getOption("overlapStartWith").toDouble());
                    resultOtoList.replace(i, entry);
                    matched.append(i);
                    break;
                }
            }
        }
    }
    //设置三分之一
    if (options->getOption("makeOneThird").toBool())
    {
        for (int i = 0; i < resultOtoList.count(); ++i)
        {
            if (!matched.contains(i))
            {
                auto entry = resultOtoList.at(i);
                entry.setOverlap(entry.preUtterance() / 3);
                resultOtoList.replace(i, entry);
            }
        }
    }
    return true;
}
