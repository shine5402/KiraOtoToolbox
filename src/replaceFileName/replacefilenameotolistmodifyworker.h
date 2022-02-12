#ifndef REPLACEFILENAMEOTOLISTMODIFYWORKER_H
#define REPLACEFILENAMEOTOLISTMODIFYWORKER_H

#include <QDir>
#include <toolBase/otolistmodifyworker.h>

class ReplaceFileNameOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ReplaceFileNameOtoListModifyWorker(QObject *parent = nullptr);
    void doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList,
                OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
    bool needConfirm() const override;
    QVector<ConfirmMsg> getConfirmMsgs() const override;
    void commit() override;
private:
    //dry-run states
    bool interpretBySystemEncoding = false;
    QHash<QString, QString> replaceMap;
    QDir otoDir;
};

#endif // REPLACEFILENAMEOTOLISTMODIFYWORKER_H
