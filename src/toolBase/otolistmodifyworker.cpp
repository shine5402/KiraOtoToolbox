#include "otolistmodifyworker.h"
#include "utils/models/otolistmodel.h"
#include "utils/dialogs/showotolistdialog.h"
#include <QMessageBox>

OtoListModifyWorker::OtoListModifyWorker(QObject *parent) : QObject(parent)
{

}

void OtoListModifyWorker::doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options)
{
    Q_UNUSED(srcOtoList)
    Q_UNUSED(resultOtoList)
    Q_UNUSED(secondSaveOtoList)
    Q_UNUSED(options)
    Q_ASSERT_X(false, "OtoListModifyWorker::doWork(Abstract)", "Not implemented");
    Q_UNREACHABLE();
}

bool OtoListModifyWorker::needConfirm() const
{
    return false;
}

QVector<OtoListModifyWorker::ConfirmMsg> OtoListModifyWorker::getConfirmMsgs() const
{
    Q_UNREACHABLE();
}

bool OtoListModifyWorker::isConfirmDialogAccepted(int msgTypeId, int dialogResult) const
{
    if (msgTypeId == Dialog){
        return dialogResult == QDialog::Accepted;
    }
    if (msgTypeId == MessageBox)
    {
        return dialogResult == QMessageBox::Ok ||
                dialogResult == QMessageBox::Open ||
                dialogResult == QMessageBox::Save ||
                dialogResult == QMessageBox::SaveAll ||
                dialogResult == QMessageBox::Yes ||
                dialogResult == QMessageBox::YesToAll ||
                dialogResult == QMessageBox::Retry;
    }
    return false;
}

void OtoListModifyWorker::commit()
{
    //Do nothing
}

int OtoListModifyWorker::ConfirmMsg::typeId() const
{
    return typeId_;
}

QString OtoListModifyWorker::ConfirmMsg::brief() const
{
    return brief_;
}

std::shared_ptr<QDialog> OtoListModifyWorker::ConfirmMsg::userDialog() const
{
    return userDialog_;
}

std::shared_ptr<QDialog> OtoListModifyWorker::ConfirmMsg::generateUserDialogFromBrief() const
{
    auto msgBox = new QMessageBox();
    msgBox->setIcon(QMessageBox::Question);
    msgBox->setText(tr("Please confirm if should proceed."));
    msgBox->setInformativeText(brief_);
    msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    return std::shared_ptr<QDialog>(dynamic_cast<QDialog*>(msgBox));
}

bool OtoListModifyWorker::ConfirmMsg::isGeneratedUseDialogAccepted(int dialogResult)
{
    return dialogResult == QMessageBox::Yes;
}

void OtoListModifyWorker::ConfirmMsg::setTypeId(int newTypeId)
{
    typeId_ = newTypeId;
}

void OtoListModifyWorker::ConfirmMsg::setBrief(const QString& newBrief)
{
    brief_ = newBrief;
}

void OtoListModifyWorker::ConfirmMsg::setUserDialog(const std::shared_ptr<QDialog>& newUserDialog)
{
    userDialog_ = newUserDialog;
}
