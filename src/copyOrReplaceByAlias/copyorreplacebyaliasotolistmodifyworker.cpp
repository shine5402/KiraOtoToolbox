#include "copyorreplacebyaliasotolistmodifyworker.h"
#include "copyorreplacebyaliasrule.h"

CopyOrReplaceByAliasOtoListModifyWorker::CopyOrReplaceByAliasOtoListModifyWorker(QObject* parent):OtoListModifyWorker(parent)
{

}


bool CopyOrReplaceByAliasOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                     OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    auto rules = options.getOption("rules").value<QVector<CopyOrReplaceByAliasRule>>();
    auto behaviorCopy = options.getOption("behaviorCopy").toBool();
    auto behaviorReplace = options.getOption("behaviorReplace").toBool();

    Q_ASSERT(behaviorCopy ^ behaviorReplace);

    resultOtoList = srcOtoList;
    QMutableVectorIterator it(resultOtoList);
    while (it.hasNext()){
        auto curr = it.next();
        for (const auto& rule : qAsConst(rules)){
            if (rule.match(curr.alias())){
                curr.setAlias(rule.replace(curr.alias()));
                if (behaviorCopy)
                    it.insert(curr);
                if (behaviorReplace)
                    it.setValue(curr);
                break;
            }
        }
    }
    return true;
}
