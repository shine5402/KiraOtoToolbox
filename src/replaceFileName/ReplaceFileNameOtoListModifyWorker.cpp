#include "ReplaceFileNameOtoListModifyWorker.h"

#include <QTextStream>

#include <ranges>

#include "FileNameReplaceMapTableModel.h"
#include "utils/dialogs/TableViewDialog.h"
#include "utils/misc/Misc.h"
#include "utils/widgets/ReplaceRule.h"

ReplaceFileNameOtoListModifyWorker::ReplaceFileNameOtoListModifyWorker(QObject *parent) : OtoListModifyWorker{parent}
{
}

void ReplaceFileNameOtoListModifyWorker::doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                                                OtoEntryList &secondSaveOtoList, const OptionContainer &options)
{
    Q_UNUSED(secondSaveOtoList)

    auto otoFileName = options.getOption("load/fileName").toString();
    otoDir = QFileInfo{otoFileName}.dir();
    interpretBySystemEncoding = options.getOption("interpretBySystemEncoding").toBool();

    auto rules = options.getOption("rules").value<QVector<ReplaceRule>>();

    QSet<QString> fileNameSet;
    for (const auto &entry : srcOtoList)
        fileNameSet.insert(entry.fileName());
    auto fileNames = fileNameSet.values();

    for (const auto &fileName : qAsConst(fileNames)) {
        auto fileInfo = QFileInfo(fileName);
        auto baseName = fileInfo.baseName();
        auto newBaseName = baseName;
        auto extension = fileInfo.completeSuffix();
        for (const auto &rule : qAsConst(rules)) {
            if (rule.match(newBaseName)) {
                newBaseName = rule.replace(newBaseName);
            }
        }
        auto newFileName = newBaseName + "." + extension;
        if (fileName != newFileName)
            replaceMap.insert(fileName, newFileName);
    }

    resultOtoList =
        srcOtoList | std::views::transform([&](OtoEntry entry) -> OtoEntry {
            if (replaceMap.contains(entry.fileName()))
                entry.setFileName(replaceMap.value(entry.fileName()));
            return entry;
        }) |
        std::ranges::to<OtoEntryList>();
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
                        "This dialog show file name in Unicode, we will convert it to system encoding in renaming if "
                        "you are willing to."));

    return {ConfirmMsg(Dialog, tr("%1 files will be renamed.").arg(replaceMap.count()),
                       std::shared_ptr<QDialog>(dynamic_cast<QDialog *>(dialog)))};
}

void ReplaceFileNameOtoListModifyWorker::commit()
{
    QFile file;
    QHash<QString, QString> renamed;
    for (auto it = replaceMap.constBegin(); it != replaceMap.constEnd(); ++it) {
        auto fileName = it.key();
        auto newFileName = it.value();
        Q_ASSERT(fileName != newFileName);
        auto actualFileName = interpretBySystemEncoding ? Misc::getFileNameInSystemEncoding(fileName) : fileName;
        auto actualNewFileName =
            interpretBySystemEncoding ? Misc::getFileNameInSystemEncoding(newFileName) : newFileName;
        auto actualFilePath = otoDir.filePath(actualFileName);
        auto actualNewFilePath = otoDir.filePath(actualNewFileName);
        file.setFileName(actualFilePath);
        if (file.rename(actualNewFilePath))
            renamed.insert(actualFilePath, actualNewFilePath);
        else {
            QString renamedInfo;
            QTextStream stream(&renamedInfo);
            for (auto it = renamed.constBegin(); it != renamed.constEnd(); ++it) {
                stream << tr("%1 -> %2").arg(it.key(), it.value()) << Qt::endl;
            }
            throw ToolException(tr("Failed to rename %1 to %2. Caused by \"%4\".\n"
                                   "These files are already renamed:\n%3")
                                    .arg(actualFilePath, actualNewFilePath, renamedInfo, file.errorString()));
        }
    }
}
