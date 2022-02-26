#ifndef SHOWOTOLISTDIALOG_H
#define SHOWOTOLISTDIALOG_H

#include <QDialog>
#include <otoentry.h>
#include "../models/otolistmodel.h"
#include <kira/dialogs/tableviewdialog.h>
#include <QDialogButtonBox>

class ShowOtoListDialog : public TableViewDialog
{
    Q_OBJECT

public:
    ShowOtoListDialog(const OtoEntryList* entryList, QWidget *parent = nullptr);
    ~ShowOtoListDialog();

private:
    const OtoEntryList* entryList = nullptr;
    OtoListModel* model;
};

#endif // SHOWOTOLISTDIALOG_H
