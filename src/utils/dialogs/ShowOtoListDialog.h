#ifndef SHOWOTOLISTDIALOG_H
#define SHOWOTOLISTDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>

#include "../models/otolistmodel.h"
#include "otoUtils/OtoEntry.h"
#include "utils/dialogs/TableViewDialog.h"

class ShowOtoListDialog : public TableViewDialog
{
    Q_OBJECT

public:
    ShowOtoListDialog(const OtoEntryList *entryList, QWidget *parent = nullptr);
    ~ShowOtoListDialog();

private:
    const OtoEntryList *entryList = nullptr;
    OtoListModel *model;
};

#endif // SHOWOTOLISTDIALOG_H
