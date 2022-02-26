#ifndef OTOPROCESSOR_H
#define OTOPROCESSOR_H

#include <QObject>
#include <otoentry.h>
#include "optioncontainer.h"
#include "toolexception.h"
#include <QDialog>

class OtoListModifyWorker : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit OtoListModifyWorker(QObject *parent = nullptr);
    virtual void doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList,
                               const OptionContainer& options);

    /*
     * If you need user to confirm extra things during processing other than save in the end,
     * or you need confirm modifications on files other than oto file itself,
     * you can return true in needConfirm(), then return these ConfirmMsgs in getConfirmMsgs().
     * We will also call commit after user confirm all msgs, so you can do external modifications here.
     */
    virtual bool needConfirm() const;

    class ConfirmMsg {
    public:
        ConfirmMsg(){};
        ConfirmMsg(int typeId, QString brief, std::shared_ptr<QDialog> userDialog = {}):typeId_(typeId), brief_(std::move(brief)), userDialog_(std::move(userDialog)){}
        int typeId() const;
        QString brief() const;
        std::shared_ptr<QDialog> userDialog() const;

        std::shared_ptr<QDialog> generateUserDialogFromBrief() const;
        static bool isGeneratedUseDialogAccepted(int dialogResult);
        void setTypeId(int newTypeId);

        void setBrief(const QString& newBrief);

        void setUserDialog(const std::shared_ptr<QDialog>& newUserDialog);

    private:
        int typeId_ = Dialog;
        QString brief_;
        std::shared_ptr<QDialog> userDialog_;

    };
    virtual QVector<ConfirmMsg> getConfirmMsgs() const;
    enum ConfirmMsgTypeId {
        Dialog = 0, MessageBox
    };
    virtual bool isConfirmDialogAccepted(int msgTypeId, int dialogResult) const;

    virtual void commit();//should save last doWork status in Worker instance itself
    //TODO: secondSaveUsage

};

#endif // OTOPROCESSOR_H
