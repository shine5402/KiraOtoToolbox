#include "removeblankotolistmodifyworker.h"

RemoveBlankOtoListModifyWorker::RemoveBlankOtoListModifyWorker(QObject* parent) : OtoListModifyWorker(parent)
{

}

bool RemoveBlankOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    resultOtoList.clear();

    auto isBlank = [&options](const OtoEntry& oto) -> bool {
        auto ignoreRight = options.getOption("ignoreRight").toBool();
        auto rightFlag = (ignoreRight && (oto.right() <= 0)) || oto.right() == 0.0;
        return oto.alias().isEmpty() && oto.left() == 0.0 && oto.consonant() == 0.0 && rightFlag && oto.preUtterance() == 0.0 && oto.overlap() == 0.0;
    };
    for (const auto& i : srcOtoList){
        if (!isBlank(i)){
            resultOtoList.append(i);
        }
    }
    return true;
}
