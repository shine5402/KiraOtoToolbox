#include "TempoTransformOtoListModifyWorker.h"

#include <numeric>
#include <ranges>

TempoTransformOtoListModifyWorker::TempoTransformOtoListModifyWorker(QObject *parent) : OtoListModifyWorker{parent}
{
}

void TempoTransformOtoListModifyWorker::doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                                               OtoEntryList &secondSaveOtoList, const OptionContainer &options)
{
    Q_UNUSED(secondSaveOtoList)

    auto offset = options.getOption("offset").toDouble();
    auto fromTempo = options.getOption("fromTempo").toDouble();
    auto toTempo = options.getOption("toTempo").toDouble();
    auto absolutePre = [](const OtoEntry &entry) -> double {
        return entry.left() + entry.preUtterance();
    };
    auto stdSrc = std::vector(srcOtoList.begin(), srcOtoList.end());

    // Group by fileName (entries are assumed sorted by fileName in oto.ini)
    std::vector<std::vector<OtoEntry>> groups;
    for (std::size_t i = 0; i < stdSrc.size();) {
        std::size_t j = i + 1;
        while (j < stdSrc.size() && stdSrc[j].fileName() == stdSrc[i].fileName())
            ++j;
        groups.emplace_back(stdSrc.begin() + i, stdSrc.begin() + j);
        i = j;
    }

    std::vector<OtoEntry> stdResult;
    for (const auto &entrys : groups) {
        auto distances =
            entrys | std::views::adjacent<2> |
            std::views::transform([&](const auto &pair) -> double {
                const auto &[a, b] = pair;
                return absolutePre(b) - absolutePre(a);
            }) |
            std::ranges::to<std::vector<double>>();

        auto ratio = fromTempo / toTempo;
        auto newDistances =
            distances | std::views::transform([&](double d) -> double { return d * ratio; }) |
            std::ranges::to<std::vector<double>>();

        auto diff =
            std::views::zip(newDistances, distances) |
            std::views::transform([](const auto &pair) -> double {
                const auto &[lhs, rhs] = pair;
                return lhs - rhs;
            }) |
            std::ranges::to<std::vector<double>>();
        diff.insert(diff.begin(), 0.0);

        auto transformed =
            std::views::zip(entrys, diff) |
            std::views::transform([&](const auto &pair) -> OtoEntry {
                const auto &[entry, d] = pair;
                auto result = entry;
                result.setLeft(result.left() + d + offset);
                if (result.right() > 0)
                    result.setRight(result.right() - (d + offset));
                return result;
            }) |
            std::ranges::to<std::vector<OtoEntry>>();

        stdResult.insert(stdResult.end(), transformed.begin(), transformed.end());
    }

    resultOtoList = QList(stdResult.begin(), stdResult.end());
}
