#include "RemoveSpecificEntriesOtoListModifyWorker.h"

#include "RemoveSpecificEntriesOptionWidget.h"

#include <ranges>

RemoveSpecificEntriesOtoListModifyWorker::RemoveSpecificEntriesOtoListModifyWorker(QObject *parent)
    : OtoListModifyWorker(parent)
{
}

void RemoveSpecificEntriesOtoListModifyWorker::doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                                                      OtoEntryList &secondSaveOtoList, const OptionContainer &options)
{
    Q_UNUSED(secondSaveOtoList)

    auto matchStrategy = (RemoveSpecificEntriesOptionWidget::MatchStrategy)options.getOption("matchStrategy").toInt();
    auto pattern = options.getOption("pattern").toString();
    auto caseSensitive = options.getOption("caseSensitive").toBool() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    resultOtoList =
        srcOtoList | std::views::filter([=](const OtoEntry &entry) -> bool {
            switch (matchStrategy) {
            case RemoveSpecificEntriesOptionWidget::Exact:
                return entry.alias().compare(pattern, caseSensitive) != 0;
            case RemoveSpecificEntriesOptionWidget::Partial:
                return !entry.alias().contains(pattern, caseSensitive);
            case RemoveSpecificEntriesOptionWidget::Regex:
                return !entry.alias().contains(QRegularExpression(
                    pattern, caseSensitive == Qt::CaseInsensitive ? QRegularExpression::CaseInsensitiveOption
                                                                  : QRegularExpression::NoPatternOption));
            default:
                Q_UNREACHABLE();
            }
        }) |
        std::ranges::to<OtoEntryList>();
}
