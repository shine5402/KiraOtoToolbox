#include "showotolistdialog.h"

ShowOtoListDialog::ShowOtoListDialog(const OtoEntryList* entryList, QWidget *parent) :
    TableViewDialog(parent), entryList(entryList)
{
    if (!entryList){
       setLabel("Error: Empty pointer.");
       return;
    }
    model = new OtoListModel(entryList, this);
    tableView->setModel(model);
    setLabel(tr("There are %1 oto entries.").arg(entryList->count()));
}


ShowOtoListDialog::~ShowOtoListDialog()
{
}
