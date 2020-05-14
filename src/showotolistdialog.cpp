#include "showotolistdialog.h"
#include "ui_showotolistdialog.h"

ShowOtoListDialog::ShowOtoListDialog(OtoEntryList* entryList, QWidget *parent) :
    QDialog(parent), ui(new Ui::ShowOtoListDialog), entryList(entryList), model(entryList, this)
{
    ui->setupUi(this);
    if (!entryList)
        ui->label->setText(tr("传入的原音设定列表指针为空指针。"));
    ui->tableView->setModel(&model);
    ui->label->setText(tr("共有 %1 条原音设定。").arg(entryList->count()));
}

ShowOtoListDialog::~ShowOtoListDialog()
{
    delete ui;
}

void ShowOtoListDialog::setLabel(const QString& label)
{
    ui->label->setText(label);
}

void ShowOtoListDialog::setStandardButtons(QDialogButtonBox::StandardButtons buttons)
{
    ui->buttonBox->setStandardButtons(buttons);
}
