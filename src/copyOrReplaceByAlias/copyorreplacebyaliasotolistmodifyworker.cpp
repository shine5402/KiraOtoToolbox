#include "copyorreplacebyaliasotolistmodifyworker.h"
#include "utils/widgets/replacerule.h"

CopyOrReplaceByAliasOtoListModifyWorker::CopyOrReplaceByAliasOtoListModifyWorker(QObject* parent):OtoListModifyWorker(parent)
{

}


void CopyOrReplaceByAliasOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                     OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    auto rules = options.getOption("rules").value<QVector<ReplaceRule>>();
    auto behaviorCopy = options.getOption("behaviorCopy").toBool();
    auto behaviorReplace = options.getOption("behaviorReplace").toBool();
    auto opStrategy = options.getOption("opStrategy").toInt();

    Q_ASSERT(behaviorCopy ^ behaviorReplace);

    resultOtoList = srcOtoList;
    QMutableVectorIterator it(resultOtoList);
    while (it.hasNext()){
        auto curr = it.next();
        auto matched = false;
        for (const auto& rule : qAsConst(rules)){
            auto origAlias = curr.alias();
            if (rule.match(curr.alias())){
                matched |= true;
                curr.setAlias(rule.replace(curr.alias()));
                if (opStrategy == 0)   //Match first then stop
                    break;
                if (opStrategy == 2){  //Match all in parallel and copy all matches (copy mode only)
                    it.insert(curr);
                    curr.setAlias(origAlias);
                }
            }
        }
        if (opStrategy != 2 && matched)//Match all and replace all matches
        {
            if (behaviorCopy)
                it.insert(curr);
            if (behaviorReplace)
                it.setValue(curr);
        }
    }
}
