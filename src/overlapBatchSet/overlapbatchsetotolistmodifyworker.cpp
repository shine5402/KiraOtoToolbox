#include "overlapbatchsetotolistmodifyworker.h"

OverlapBatchSetOtoListModifyWorker::OverlapBatchSetOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

bool OverlapBatchSetOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)
    resultOtoList = srcOtoList;

    QVector<int> matched;
    //Matching start pattern and set ovl for them
    if (options.getOption("ifSetOverlapStartWith").toBool())
    {
        for (int i = 0; i < resultOtoList.count(); ++i)
        {
            auto entry = resultOtoList.at(i);
            auto patternList = options.getOption("startWithPatternList").toStringList();
            for (const auto &s : std::as_const(patternList))
            {
                if (entry.alias().startsWith(s) || (options.getOption("ifMatchStartOto").toBool() && entry.alias().startsWith("- " + s)))
                {
                    entry.setOverlap(options.getOption("overlapStartWith").toDouble());
                    resultOtoList.replace(i, entry);
                    matched.append(i);
                    break;
                }
            }
        }
    }
    //Set 1/3
    if (options.getOption("makeOneThird").toBool())
    {
        for (int i = 0; i < resultOtoList.count(); ++i)
        {
            if (!matched.contains(i))
            {
                auto entry = resultOtoList.at(i);
                auto result = entry.preUtterance() / 3;
                if (options.getOption("oneSecondWhenTooSmall").toBool() && result < options.getOption("oneSecondWhenTooSmallValue").toDouble())
                    result = entry.preUtterance() / 2;
                entry.setOverlap(result);
                resultOtoList.replace(i, entry);
            }
        }
    }
    return true;
}
