#ifndef JAVASCRIPTTOOLOTOLISTMODIFYWORKER_H
#define JAVASCRIPTTOOLOTOLISTMODIFYWORKER_H

#include <QDir>
#include <toolBase/otolistmodifyworker.h>

class JavaScriptToolWAVFileAPI : public QObject {
    Q_OBJECT
public:
    JavaScriptToolWAVFileAPI(QDir otoDir, bool interpretBySystemEncoding, QObject* parent)
        : QObject(parent), otoDir(std::move(otoDir)), interpretBySystemEncoding(interpretBySystemEncoding) {};
    const QHash<QString, QString>& renameMap() const;

public slots:
    //In the same dir of oto.ini
    void renameFile(const QString& fileName, const QString& newFileName);
    int getWAVLength(const QString& fileName);

private:
    QHash<QString, QString> renameMap_;
    QDir otoDir;
    bool interpretBySystemEncoding = false;
};

class JavaScriptToolOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit JavaScriptToolOtoListModifyWorker(QObject *parent = nullptr);
    ~JavaScriptToolOtoListModifyWorker();
    void doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
    bool needConfirm() const override;
    QVector<ConfirmMsg> getConfirmMsgs() const override;
    void commit() override;

private:
    JavaScriptToolWAVFileAPI* fileAPI = nullptr;
    static QString consoleOutput;
    static QtMessageHandler defaultMsgHandler;
    static void jsConsoleMsgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
};

#endif // JAVASCRIPTTOOLOTOLISTMODIFYWORKER_H
