#include "CVVCPartSplitOtoListModifyWorker.h"

#include <QRegularExpression>

#include <algorithm>
#include <ranges>

#include "utils/misc/Misc.h"

CVVCPartSplitOtoListModifyWorker::CVVCPartSplitOtoListModifyWorker(QObject *parent) : OtoListModifyWorker(parent)
{
}

void CVVCPartSplitOtoListModifyWorker::doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                                              OtoEntryList &secondSaveOtoList, const OptionContainer &options)
{
    auto isSeeBeginPatternAsCV = options.getOption("isSeeBeginPatternAsCV").toBool();
    auto seeBeginPatternAsCVContent = options.getOption("seeBeginPatternAsCVContent").toStringList();
    auto isSeeEndPatternAsCV = options.getOption("isSeeEndPatternAsCV").toBool();
    auto seeEndPatternAsCVContent = options.getOption("seeEndPatternAsCVContent").toStringList();
    auto shouldCopyCVasStartOto = options.getOption("copyCVtoStartOto").toBool();

    auto isAliasEmpty = [](const OtoEntry &entry) -> bool {
        return entry.alias().isEmpty();
    };
    auto emptyDropped =
        srcOtoList | std::views::filter(std::not_fn(isAliasEmpty)) | std::ranges::to<OtoEntryList>();
    auto emptyPart =
        srcOtoList | std::views::filter(isAliasEmpty) | std::ranges::to<OtoEntryList>();

    auto isCVPart = [isSeeBeginPatternAsCV, seeBeginPatternAsCVContent, isSeeEndPatternAsCV,
                     seeEndPatternAsCVContent](const OtoEntry &entry) -> bool {
        auto notDividedBySpace = !QRegularExpression{".* .*"}.match(entry.alias()).hasMatch();
        bool matchedByBeginPattern = false;
        bool matchedByEndPattern = false;
        if (isSeeBeginPatternAsCV) {
            for (const auto &currentPattern : seeBeginPatternAsCVContent) {
                matchedByBeginPattern |=
                    QRegularExpression{QString{"%1 .*"}.arg(currentPattern)}.match(entry.alias()).hasMatch();
            }
        }
        if (isSeeEndPatternAsCV) {
            for (const auto &currentPattern : seeEndPatternAsCVContent) {
                matchedByEndPattern |=
                    QRegularExpression{QString{".* %1"}.arg(currentPattern)}.match(entry.alias()).hasMatch();
            }
        }
        return notDividedBySpace || matchedByBeginPattern || matchedByEndPattern;
    };
    auto CVList =
        emptyDropped | std::views::filter(isCVPart) | std::ranges::to<OtoEntryList>();
    VCList =
        emptyDropped | std::views::filter(std::not_fn(isCVPart)) | std::ranges::to<OtoEntryList>();

    OtoEntryList startList;
    if (shouldCopyCVasStartOto) {
        auto cvWithoutStart =
            CVList |
            std::views::filter([&](const auto &entry) {
                return std::ranges::find_if(
                           srcOtoList,
                           [&](const auto &entryInter) { return entryInter.alias() == "- " + entry.alias(); }) ==
                       srcOtoList.end();
            }) |
            std::ranges::to<OtoEntryList>();
        startList =
            cvWithoutStart |
            std::views::transform([](auto entry) {
                entry.setAlias("- " + entry.alias());
                return entry;
            }) |
            std::ranges::to<OtoEntryList>();
    }

    auto saveOptions = options.extract("save/");
    auto isSecondFileNameUsed = saveOptions.getOption("isSecondFileNameUsed").toBool();
    VCExtractedToNewFile = isSecondFileNameUsed;
    if (isSecondFileNameUsed) {
        resultOtoList =
            QList<OtoEntryList>{CVList, startList, emptyPart} | std::views::join | std::ranges::to<OtoEntryList>();
        secondSaveOtoList = VCList;
    } else {
        resultOtoList =
            QList<OtoEntryList>{CVList, startList, emptyPart, VCList} | std::views::join | std::ranges::to<OtoEntryList>();
    }
}

bool CVVCPartSplitOtoListModifyWorker::needConfirm() const
{
    return VCExtractedToNewFile;
}

QVector<OtoListModifyWorker::ConfirmMsg> CVVCPartSplitOtoListModifyWorker::getConfirmMsgs() const
{
    return {{Dialog,
             tr("%1 oto entries, which is recognized as VC part, will be saved to the path you specified.")
                 .arg(VCList.count()),
             std::shared_ptr<QDialog>(dynamic_cast<QDialog *>(Misc::getAskUserWithShowOtoListDialog(
                 VCList, tr("VC part extracted"),
                 tr("These %1 oto entries will be save to location specified.").arg(VCList.count()), nullptr)))}};
}
