#include "tempotransformotolistmodifyworker.h"
#include <kira/lib_helper/fplus_qt_adapter.h>

TempoTransformOtoListModifyWorker::TempoTransformOtoListModifyWorker(QObject *parent)
    : OtoListModifyWorker{parent}
{

}


void TempoTransformOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                               OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    auto offset = options.getOption("offset").toDouble();
    auto fromTempo = options.getOption("fromTempo").toDouble();
    auto toTempo = options.getOption("toTempo").toDouble();
    //TODO: extract to OtoEntry itself
    auto absolutePre = [](const OtoEntry& entry)->double{
        return entry.left() + entry.preUtterance();
    };
    auto stdSrc = std::vector(srcOtoList.begin(), srcOtoList.end());
    auto stdResult = fplus::transform_and_concat([&](const std::vector<OtoEntry>& entrys)->std::vector<OtoEntry>{
        auto distances = fplus::transform([&](const std::pair<OtoEntry, OtoEntry>& pair)->double{
            return absolutePre(pair.second) - absolutePre(pair.first);
        },fplus::zipWithNext(entrys));
        auto newDistances = fplus::transform([&](double distance)->double{
            auto ratio = fromTempo / toTempo;
            return distance * ratio;
        }, distances);
        auto diff = fplus::zip_with([](double lhs, double rhs)->double{
            return lhs - rhs;
        }, newDistances, distances);
        diff.insert(diff.begin(), 0.0);
        return fplus::transform([&](const std::pair<OtoEntry, double>& pair)->OtoEntry{
            auto entry = pair.first;
            entry.setLeft(entry.left() + pair.second + offset);
            if (entry.right() > 0)
                entry.setRight(entry.right() - (pair.second + offset));
            return entry;
        },
        fplus::zip(entrys, diff));
    },
    fplus::group_by([](const OtoEntry& lhs, const OtoEntry& rhs)->bool{
        return lhs.fileName() == rhs.fileName();
    }, stdSrc));
    resultOtoList = QList(stdResult.begin(), stdResult.end());
}
