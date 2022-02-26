#include "cv_vcpartsplitotolistmodifyworker.h"
#include "utils/misc/misc.h"
#include <fplus/fplus.hpp>
#include <QRegularExpression>
#include <kira/lib_helper/fplus_qt_adapter.h>

CV_VCPartSplitOtoListModifyWorker::CV_VCPartSplitOtoListModifyWorker(QObject *parent) : OtoListModifyWorker(parent)
{

}

void CV_VCPartSplitOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    auto isSeeBeginPatternAsCV = options.getOption("isSeeBeginPatternAsCV").toBool();
    auto seeBeginPatternAsCVContent = options.getOption("seeBeginPatternAsCVContent").toStringList();
    auto isSeeEndPatternAsCV = options.getOption("isSeeEndPatternAsCV").toBool();
    auto seeEndPatternAsCVContent = options.getOption("seeEndPatternAsCVContent").toStringList();

    auto isAliasEmpty = [](const OtoEntry& entry) -> bool{
        return entry.alias().isEmpty();
    };
    auto emptyDropped = fplus::drop_if(isAliasEmpty, srcOtoList);
    auto emptyPart = fplus::keep_if(isAliasEmpty, srcOtoList);

    auto isCVPart = [isSeeBeginPatternAsCV, seeBeginPatternAsCVContent, isSeeEndPatternAsCV, seeEndPatternAsCVContent](const OtoEntry& entry) -> bool{
        auto notDividedBySpace = !QRegularExpression{".* .*"}.match(entry.alias()).hasMatch();
        bool matchedByBeginPattern = false;
        bool matchedByEndPattern = false;
        if (isSeeBeginPatternAsCV)
        {
            for (const auto& currentPattern : seeBeginPatternAsCVContent){
                matchedByBeginPattern |= QRegularExpression{QString{"%1 .*"}.arg(currentPattern)}.match(entry.alias()).hasMatch();
            }
        }
        if (isSeeEndPatternAsCV)
        {
            for (const auto& currentPattern : seeEndPatternAsCVContent){
                matchedByEndPattern |= QRegularExpression{QString{".* %1"}.arg(currentPattern)}.match(entry.alias()).hasMatch();
            }
        }
        return notDividedBySpace || matchedByBeginPattern || matchedByEndPattern;
    };
    auto CVList = fplus::keep_if(isCVPart, emptyDropped);
    VCList = fplus::drop_if(isCVPart, emptyDropped);

    auto saveOptions = options.extract("save/");
    auto isSecondFileNameUsed = saveOptions.getOption("isSecondFileNameUsed").toBool();
    VCExtractedToNewFile = isSecondFileNameUsed;
    if (isSecondFileNameUsed){
        resultOtoList = fplus::append(CVList, emptyPart);
        secondSaveOtoList = VCList;
    }
    else{
        resultOtoList = fplus::concat(QList{CVList, emptyPart, VCList});
    }
}


bool CV_VCPartSplitOtoListModifyWorker::needConfirm() const
{
    return VCExtractedToNewFile;
}

QVector<OtoListModifyWorker::ConfirmMsg> CV_VCPartSplitOtoListModifyWorker::getConfirmMsgs() const
{
    return {{Dialog,
             tr("%1 oto entries, which is recognized as VC part, will be saved to the path you specified.").arg(VCList.count()),
             std::shared_ptr<QDialog>(dynamic_cast<QDialog*>(Misc::getAskUserWithShowOtoListDialog(VCList,
                                          tr("VC part extracted"),
                                          tr("These %1 oto entries will be save to location specified.").arg(VCList.count()),
                                          nullptr)))
        }};
}

