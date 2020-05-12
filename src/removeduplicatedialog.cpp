#include "removeduplicatedialog.h"
#include "ui_removeduplicatedialog.h"

RemoveDuplicateDialog::RemoveDuplicateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveDuplicateDialog)
{
    ui->setupUi(this);
}

RemoveDuplicateDialog::~RemoveDuplicateDialog()
{
    delete ui;
}
