#include "replacefilenameotolistmodifyworker.h"
#include "utils/misc/misc.h"
#include "utils/widgets/replacerule.h"
#include <kira/lib_helper/fplus_qt_adapter.h>
#include <kira/dialogs/tableviewdialog.h>
#include "filenamereplacemaptablemodel.h"
#include <QTextStream>

ReplaceFileNameOtoListModifyWorker::ReplaceFileNameOtoListModifyWorker(QObject *parent)
    : OtoListModifyWorker{parent}
{

}


void ReplaceFileNameOtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                                                OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(secondSaveOtoList)

    auto otoFileName = options.getOption("load/fileName").toString();
    otoDir = QFileInfo{otoFileName}.dir();
    interpretBySystemEncoding = options.getOption("interpretBySystemEncoding").toBool();

    auto rules = options.getOption("rules").value<QVector<ReplaceRule>>();

    auto fileNames = fplus::unique(fplus::transform([](const OtoEntry& entry)->QString{
        return entry.fileName();
    }, srcOtoList));

    for (const auto& fileName : qAsConst(fileNames)){
        auto fileInfo = QFileInfo(fileName);
        auto baseName = fileInfo.baseName();
        auto newBaseName = baseName;
        auto extension = fileInfo.completeSuffix();
        for (const auto& rule : qAsConst(rules)){
            if (rule.match(newBaseName)){
                newBaseName = rule.replace(newBaseName);
            }
        }
        auto newFileName = newBaseName + "." + extension;
        if (fileName != newFileName)
            replaceMap.insert(fileName, newFileName);
    }

    resultOtoList = fplus::transform([&](OtoEntry entry)->OtoEntry{
            if (replaceMap.contains(entry.fileName()))
                entry.setFileName(replaceMap.value(entry.fileName()));
            return entry;
    }, srcOtoList);
}


bool ReplaceFileNameOtoListModifyWorker::needConfirm() const
{
    return true;
}

QVector<OtoListModifyWorker::ConfirmMsg> ReplaceFileNameOtoListModifyWorker::getConfirmMsgs() const
{
    auto dialog = new TableViewDialog;
    auto model = new FileNameReplaceMapTableModel(replaceMap, dialog);
    dialog->setModel(model);
    dialog->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    dialog->setLabel(tr("These file will be renamed. This operation can NOT be UNDONE.\n"
                        "This dialog show file name in Unicode, we will convert it to system encoding in renaming if you are willing to."));

    return {ConfirmMsg(Dialog, tr("%1 files will be renamed.").arg(replaceMap.count()), std::shared_ptr<QDialog>(dynamic_cast<QDialog*>(dialog)))};
}

void ReplaceFileNameOtoListModifyWorker::commit()
{
    QFile file;
    QHash<QString, QString> renamed;
    for (auto it = replaceMap.constBegin(); it != replaceMap.constEnd(); ++it){
        auto fileName = it.key();
        auto newFileName = it.value();
        Q_ASSERT(fileName != newFileName);
        auto actualFileName = interpretBySystemEncoding ? Misc::getFileNameInSystemEncoding(fileName) : fileName;
        auto actualNewFileName = interpretBySystemEncoding ? Misc::getFileNameInSystemEncoding(newFileName) : newFileName;
        auto actualFilePath = otoDir.filePath(actualFileName);
        auto actualNewFilePath = otoDir.filePath(actualNewFileName);
        file.setFileName(actualFilePath);
        if (file.rename(actualNewFilePath))
            renamed.insert(actualFilePath, actualNewFilePath);
        else
        {
            QString renamedInfo;
            QTextStream stream(&renamedInfo);
            for (auto it = renamed.constBegin(); it != renamed.constEnd(); ++it){
                stream << tr("%1 -> %2").arg(it.key(), it.value()) << Qt::endl;
            }
            throw ToolException(tr("Failed to rename %1 to %2. Caused by \"%4\".\n"
                                   "These files are already renamed:\n%3").arg(actualFilePath, actualNewFilePath,
                                                                               renamedInfo, file.errorString()));
        }
    }
}
