#include "vowelcrossfadingotolistmodifyworker.h"
#include <kira/lib_helper/fplus_qt_adapter.h>

VowelCrossfadingOtoListModifyWorker::VowelCrossfadingOtoListModifyWorker(QObject* parent):OtoListModifyWorker(parent)
{

}


void VowelCrossfadingOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                 OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    resultOtoList = srcOtoList;

    auto CVList = options.getOption("CVList").toStringList();
    auto VList = options.getOption("VList").toStringList();
    auto longRecordingPattern = options.getOption("longRecordingPattern").toStringList();
    auto longRecordingList = fplus::unique(
                    fplus::transform_and_concat(
                        [longRecordingPattern](const QString& alias)->QList<QString>{
        return fplus::transform([alias](QString pattern)->QString{
            return pattern.replace("%a", alias);
        }, longRecordingPattern);
    }, CVList + VList));

    auto containsAlias = [&](const QStringList& patterns, const QString& alias) -> bool{
        return patterns.contains(alias) ||
                (options.getOption("removeNumberSuffixWhenMatching").toBool() &&
                 patterns.contains(OtoEntryFunctions::removeDigitSuffix(alias)));
    };

    if (options.getOption("doCVCrossfading").toBool())
    {
        auto preUtterance = options.getOption("CVPreUtterance").toDouble();
        auto overlap = options.getOption("CVOverlap").toDouble();
        auto matchList = CVList + longRecordingList;
        QMutableListIterator it(resultOtoList);
        while (it.hasNext()){
            auto entry = it.next();
            if (containsAlias(matchList, it.value().alias()))
            {
                entry.setPreUtterance(preUtterance);
                entry.setOverlap(overlap);
                Q_ASSERT(options.getOption("CVBehaviourOverride").toBool() ^ options.getOption("CVBehaviourCopy").toBool());
                if (options.getOption("CVBehaviourOverride").toBool()){
                    it.setValue(entry);
                }
                if (options.getOption("CVBehaviourCopy").toBool())
                {
                    entry.setAlias(QLatin1String("* %1").arg(entry.alias()));
                    it.insert(entry);
                }
            }
        }
    }

    if (options.getOption("VVOverlapIncrease").toBool()){
        auto VVList = fplus::transform_and_concat([VList](const QString& CV)->QList<QString>{
            return fplus::transform([CV](const QString& V)->QString{
                return V + " " + CV;
            }, VList);
        }, CVList);

        resultOtoList = fplus::transform([VVList, containsAlias](OtoEntry entry){
            if (containsAlias(VVList, entry.alias())){
                entry.setOverlap(entry.preUtterance() / 2);
            }
                return entry;
        }, resultOtoList);
    }
}
