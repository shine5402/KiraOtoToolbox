#include "cv_vcpartsplitotolistmodifyworker.h"
#include <fplus/fplus.hpp>
#include <QRegularExpression>
#include <kira/lib_helper/fplus_qt_adapter.h>

CV_VCPartSplitOtoListModifyWorker::CV_VCPartSplitOtoListModifyWorker(QObject *parent) : OtoListModifyWorker(parent)
{

}

bool CV_VCPartSplitOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
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
    auto VCList = fplus::drop_if(isCVPart, emptyDropped);

    auto saveOptions = options.extract("save/");
    auto isSecondFileNameUsed = saveOptions.getOption("isSecondFileNameUsed").toBool();
    if (isSecondFileNameUsed){
        resultOtoList = fplus::append(CVList, emptyPart);
        secondSaveOtoList = VCList;
    }
    else{
        resultOtoList = fplus::concat(QVector{CVList, emptyPart, VCList});
    }
    return true;
}
