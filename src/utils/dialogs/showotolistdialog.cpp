#include "showotolistdialog.h"

ShowOtoListDialog::ShowOtoListDialog(const OtoEntryList* entryList, QWidget *parent) :
    TableViewDialog(parent), entryList(entryList)
{
    if (!entryList){
       setLabel(tr("传入的原音设定列表指针为空指针。"));
       return;
    }
    model = new OtoListModel(entryList, this);
    tableView->setModel(model);
    setLabel(tr("共有 %1 条原音设定。").arg(entryList->count()));
}


ShowOtoListDialog::~ShowOtoListDialog()
{
}
