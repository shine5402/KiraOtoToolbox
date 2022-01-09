#include "trimarounfspecificvalueotolistmodifyworker.h"
#include <kira/lib_helper/fplus_qt_adapter.h>

TrimArounfSpecificValueOtoListModifyWorker::TrimArounfSpecificValueOtoListModifyWorker(QObject* parent):OtoListModifyWorker(parent)
{

}

bool TrimArounfSpecificValueOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                        OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    if (!options.exists("field"))
        return false;

    auto field = (OtoEntry::OtoParameterOrder) options.getOption("field", 2).toInt();
    auto targetValue = options.getOption("targetValue").toDouble();
    auto roundingEdge = std::fabs(options.getOption("roundingRange").toDouble());

    resultOtoList = fplus::transform([=](const OtoEntry& entry)->OtoEntry{
        auto result = entry;
        auto fieldValue = entry.getParameter(field).toDouble();
        if (fieldValue > targetValue - roundingEdge && fieldValue <= targetValue + roundingEdge)
            result.setParameter(field, targetValue);
        return result;
    }, srcOtoList);

    return true;
}
