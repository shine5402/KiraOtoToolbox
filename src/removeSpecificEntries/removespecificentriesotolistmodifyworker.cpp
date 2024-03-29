#include "removespecificentriesotolistmodifyworker.h"
#include "removespecificentriesoptionwidget.h"
#include <kira/lib_helper/fplus_qt_adapter.h>

RemoveSpecificEntriesOtoListModifyWorker::RemoveSpecificEntriesOtoListModifyWorker(QObject* parent) :
    OtoListModifyWorker(parent)
{

}


void RemoveSpecificEntriesOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                      OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    auto matchStrategy = (RemoveSpecificEntriesOptionWidget::MatchStrategy) options.getOption("matchStrategy").toInt();
    auto pattern = options.getOption("pattern").toString();
    auto caseSensitive = options.getOption("caseSensitive").toBool() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    resultOtoList = fplus::drop_if([=](const OtoEntry& entry)->bool{
        switch (matchStrategy) {
        case RemoveSpecificEntriesOptionWidget::Exact:return entry.alias().compare(pattern, caseSensitive) == 0;
        case RemoveSpecificEntriesOptionWidget::Partial:return entry.alias().contains(pattern, caseSensitive);
        case RemoveSpecificEntriesOptionWidget::Regex:return entry.alias().contains(QRegExp(pattern, caseSensitive));
        default:Q_UNREACHABLE();
        }
    }, srcOtoList);
}
