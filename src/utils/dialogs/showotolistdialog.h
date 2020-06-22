#ifndef SHOWOTOLISTDIALOG_H
#define SHOWOTOLISTDIALOG_H

#include <QDialog>
#include <otoentry.h>
#include "../models/otolistmodel.h"
#include "tableviewdialog.h"
#include <QDialogButtonBox>

class ShowOtoListDialog : public TableViewDialog
{
    Q_OBJECT

public:
    ShowOtoListDialog(OtoEntryList* entryList, QWidget *parent = nullptr);
    ~ShowOtoListDialog();

private:
    OtoEntryList* entryList = nullptr;
    OtoListModel* model;
};

#endif // SHOWOTOLISTDIALOG_H
