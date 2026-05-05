#include "JavaScriptToolOtoListModifyWorker.h"

#include <QDir>
#include <QJSEngine>

#include "replaceFileName/FileNameReplaceMapTableModel.h"
#include "utils/dialogs/CommonHtmlDialog.h"
#include "utils/dialogs/TableViewDialog.h"
#include "utils/lib_helper/WavDuration.h"
#include "utils/misc/Misc.h"

JavaScriptToolOtoListModifyWorker::JavaScriptToolOtoListModifyWorker(QObject *parent) : OtoListModifyWorker{parent}
{
}

JavaScriptToolOtoListModifyWorker::~JavaScriptToolOtoListModifyWorker()
{
    // Make sure reset even when an exception was throwed
    qInstallMessageHandler(0);
}

QtMessageHandler JavaScriptToolOtoListModifyWorker::defaultMsgHandler = nullptr;
QString JavaScriptToolOtoListModifyWorker::consoleOutput{};

void JavaScriptToolOtoListModifyWorker::doWork(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList,
                                               OtoEntryList &secondSaveOtoList, const OptionContainer &options)
{
    // TODO: maybe implement it later
    Q_UNUSED(secondSaveOtoList)

    auto jsEngine = new QJSEngine(this);
    // MetaObj(Classes)
    auto otoEntryClass = jsEngine->newQMetaObject(&OtoEntry::staticMetaObject);
    jsEngine->globalObject().setProperty("OtoEntry", otoEntryClass);

    // OtoData
    auto dataArray = jsEngine->newArray(srcOtoList.count());
    for (auto i = 0; i < srcOtoList.count(); ++i) {
        dataArray.setProperty(i, jsEngine->newQObject(new OtoEntry(srcOtoList[i])));
    }
    jsEngine->globalObject().setProperty("data", dataArray);

    // File API
    auto fileName = options.getOption("load/fileName").toString();
    auto otoDir = QFileInfo{fileName}.dir();
    auto interpretBySystemEncoding = options.getOption("interpretBySystemEncoding").toBool();

    fileAPI = new JavaScriptToolWAVFileAPI(otoDir, interpretBySystemEncoding, this);
    auto fileAPIJSObj = jsEngine->toScriptValue(fileAPI);
    jsEngine->globalObject().setProperty("WAVFileAPI", fileAPIJSObj);

    // Console API
    consoleOutput.clear();
    defaultMsgHandler = qInstallMessageHandler(0);
    qInstallMessageHandler(&jsConsoleMsgHandler);
    jsEngine->installExtensions(QJSEngine::ConsoleExtension);

    // Run script
    auto script = options.getOption("script").toString();
    auto result = jsEngine->evaluate(script);
    if (result.isError())
        throw ToolException(tr("Uncaught exception when running script at line %1: %2\nStack:%3")
                                .arg(result.property("lineNumber").toInt())
                                .arg(result.toString(), result.property("stack").toString()));
    // Get data
    resultOtoList.clear();
    dataArray = jsEngine->globalObject().property("data");
    auto resultDataLength = dataArray.property("length").toInt();
    for (auto i = 0; i < resultDataLength; ++i) {
        resultOtoList.append(*qobject_cast<OtoEntry *>(dataArray.property(i).toQObject()));
    }

    // Reset Msg Handler
    qInstallMessageHandler(0);
}

bool JavaScriptToolOtoListModifyWorker::needConfirm() const
{
    return (!fileAPI->renameMap().isEmpty()) || (!consoleOutput.isEmpty());
}

QVector<OtoListModifyWorker::ConfirmMsg> JavaScriptToolOtoListModifyWorker::getConfirmMsgs() const
{
    QVector<OtoListModifyWorker::ConfirmMsg> result;
    // file rename
    if (!fileAPI->renameMap().isEmpty()) {
        auto dialog = new TableViewDialog;
        auto model = new FileNameReplaceMapTableModel(fileAPI->renameMap(), dialog);
        dialog->setModel(model);
        dialog->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        dialog->setLabel(tr("These file will be renamed. This operation can NOT be UNDONE."));
        ConfirmMsg fileRenameMsg{Dialog, tr("%1 files will be renamed.").arg(fileAPI->renameMap().count()),
                                 std::shared_ptr<QDialog>(dynamic_cast<QDialog *>(dialog))};
        result.append(fileRenameMsg);
    }

    // console output
    if (!consoleOutput.isEmpty()) {
        auto dialog = new CommonHtmlDialog;
        dialog->setMarkdown(consoleOutput);
        dialog->setLabel(tr("Console output when running script:"));
        dialog->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        ConfirmMsg consoleOutputMsg{Dialog, tr("Console output when running script."),
                                    std::shared_ptr<QDialog>(dynamic_cast<QDialog *>(dialog))};
        result.append(consoleOutputMsg);
    }

    return result;
}

void JavaScriptToolOtoListModifyWorker::commit()
{
    if (!fileAPI->renameMap().isEmpty()) {
        QFile file;
        QHash<QString, QString> renamed;
        auto renameMap = fileAPI->renameMap();
        for (auto it = renameMap.constBegin(); it != renameMap.constEnd(); ++it) {
            auto actualFileName = it.key();
            auto actualNewFileName = it.value();
            file.setFileName(actualFileName);
            if (file.rename(actualNewFileName)) {
                renamed.insert(actualFileName, actualNewFileName);
            } else {
                QString renamedInfo;
                QTextStream stream(&renamedInfo);
                for (auto it = renamed.constBegin(); it != renamed.constEnd(); ++it) {
                    stream << tr("%1 -> %2").arg(it.key(), it.value()) << Qt::endl;
                }
                throw ToolException(tr("Failed to rename %1 to %2. Caused by \"%4\".\n"
                                       "These files are already renamed:\n%3")
                                        .arg(actualFileName, actualNewFileName, renamedInfo, file.errorString()));
            }
        }
    }
}

void JavaScriptToolOtoListModifyWorker::jsConsoleMsgHandler(QtMsgType type, const QMessageLogContext &context,
                                                            const QString &msg)
{
    Q_ASSERT(defaultMsgHandler);
    if (strcmp(context.category, "js") == 0) {
        switch (type) {
        case QtDebugMsg:
            consoleOutput.append(QString("[Debug] %1").arg(msg) + "\n");
            break;
        case QtInfoMsg:
            consoleOutput.append(QString("[Info] %1").arg(msg) + "\n");
            break;
        case QtWarningMsg:
            consoleOutput.append(QString("[Warning] %1").arg(msg) + "\n");
            break;
        case QtCriticalMsg:
            consoleOutput.append(QString("[Critical] %1").arg(msg) + "\n");
            break;
        case QtFatalMsg:
            consoleOutput.append(QString("[Fatal] %1").arg(msg) + "\n");
        }
    }
    defaultMsgHandler(type, context, msg);
}

const QHash<QString, QString> &JavaScriptToolWAVFileAPI::renameMap() const
{
    return renameMap_;
}

void JavaScriptToolWAVFileAPI::renameFile(const QString &fileName, const QString &newFileName)
{
    auto actualFileName = interpretBySystemEncoding ? Misc::getFileNameInSystemEncoding(fileName) : fileName;
    auto actualNewFileName = interpretBySystemEncoding ? Misc::getFileNameInSystemEncoding(newFileName) : newFileName;
    auto actualFilePath = otoDir.filePath(actualFileName);
    auto actualNewFilePath = otoDir.filePath(actualNewFileName);
    renameMap_.insert(actualFilePath, actualNewFilePath);
}

int JavaScriptToolWAVFileAPI::getWAVLength(const QString &fileName)
{
    auto actualFileName = interpretBySystemEncoding ? Misc::getFileNameInSystemEncoding(fileName) : fileName;
    auto filePath = otoDir.filePath(actualFileName);
    if (!QFileInfo{filePath}.exists())
        throw ToolException(tr("The file \"%1\" don't exist. Please check and try again.").arg(filePath));
    auto wavLength = WavHelper::getWavDurationMs(filePath);
    if (!wavLength.has_value())
        throw ToolException(
            tr("Cannot open file \"%1\", or it contains invalid data. Please check and try again.").arg(filePath));

    return static_cast<int>(wavLength.value());
}
