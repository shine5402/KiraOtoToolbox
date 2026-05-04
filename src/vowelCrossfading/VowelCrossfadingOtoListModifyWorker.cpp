#include "VowelCrossfadingOtoListModifyWorker.h"

#include <ranges>

VowelCrossfadingOtoListModifyWorker::VowelCrossfadingOtoListModifyWorker(QObject *parent) : OtoListModifyWorker(parent)
{
}

void VowelCrossfadingOtoListModifyWorker::doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                                                 OtoEntryList &secondSaveOtoList, const OptionContainer &options)
{
    Q_UNUSED(secondSaveOtoList)

    resultOtoList = srcOtoList;

    auto CVList = options.getOption("CVList").toStringList();
    auto VList = options.getOption("VList").toStringList();
    auto longRecordingPattern = options.getOption("longRecordingPattern").toStringList();
    QSet<QString> longRecordingSet;
    auto combinedList = CVList + VList;
    for (const auto &alias : combinedList) {
        for (auto pattern : longRecordingPattern) {
            longRecordingSet.insert(pattern.replace("%a", alias));
        }
    }
    auto longRecordingList = longRecordingSet.values();

    auto containsAlias = [&](const QStringList &patterns, const QString &alias) -> bool {
        return patterns.contains(alias) || (options.getOption("removeNumberSuffixWhenMatching").toBool() &&
                                            patterns.contains(OtoEntryFunctions::removeDigitSuffix(alias)));
    };

    if (options.getOption("doCVCrossfading").toBool()) {
        auto preUtterance = options.getOption("CVPreUtterance").toDouble();
        auto overlap = options.getOption("CVOverlap").toDouble();
        auto matchList = CVList + longRecordingList;
        QMutableListIterator it(resultOtoList);
        while (it.hasNext()) {
            auto entry = it.next();
            if (containsAlias(matchList, it.value().alias())) {
                entry.setPreUtterance(preUtterance);
                entry.setOverlap(overlap);
                Q_ASSERT(options.getOption("CVBehaviourOverride").toBool() ^
                         options.getOption("CVBehaviourCopy").toBool());
                if (options.getOption("CVBehaviourOverride").toBool()) {
                    it.setValue(entry);
                }
                if (options.getOption("CVBehaviourCopy").toBool()) {
                    entry.setAlias(QLatin1String("* %1").arg(entry.alias()));
                    it.insert(entry);
                }
            }
        }
    }

    if (options.getOption("VVOverlapIncrease").toBool()) {
        auto VVList =
            CVList | std::views::transform([VList](const QString &CV) {
                return VList | std::views::transform([CV](const QString &V) -> QString { return V + " " + CV; }) |
                       std::ranges::to<QStringList>();
            }) |
            std::views::join | std::ranges::to<QStringList>();

        resultOtoList =
            resultOtoList | std::views::transform([VVList, containsAlias](OtoEntry entry) {
                if (containsAlias(VVList, entry.alias())) {
                    entry.setOverlap(entry.preUtterance() / 2);
                }
                return entry;
            }) |
            std::ranges::to<OtoEntryList>();
    }
}
