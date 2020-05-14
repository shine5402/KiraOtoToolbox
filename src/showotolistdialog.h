#ifndef SHOWOTOLISTDIALOG_H
#define SHOWOTOLISTDIALOG_H

#include <QDialog>
#include <otoentry.h>
#include "otolistmodel.h"
#include <QDialogButtonBox>

namespace Ui {
    class ShowOtoListDialog;
}

class ShowOtoListDialog : public QDialog
{
    Q_OBJECT

    using OtoEntryList = QList<OtoEntry>;
public:
    ShowOtoListDialog(OtoEntryList* entryList, QWidget *parent = nullptr);
    explicit ShowOtoListDialog(QAbstractItemModel* model, QWidget *parent = nullptr);
    ~ShowOtoListDialog();

    void setLabel(const QString& label);
    void setStandardButtons(QDialogButtonBox::StandardButtons buttons);

private:
    Ui::ShowOtoListDialog *ui;
    OtoEntryList* entryList = nullptr;
    OtoListModel* model;
};

#endif // SHOWOTOLISTDIALOG_H
