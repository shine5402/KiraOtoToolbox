#include "tooldialog.h"
#include "ui_tooldialog.h"
#ifdef SHINE5402OTOBOX_TEST
#include <QTimer>
#endif

ToolDialog::ToolDialog(ToolDialogAdapter* adapter, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolDialog),
    adapter(adapter)
{
    ui->setupUi(this);
    connect(ui->otoLoadWidget, &OtoFileLoadWidget::loaded, this, &ToolDialog::otoFileLoaded);
    adapter->setupSpecificUIWidgets(ui->rootLayout);
    reAssignUIWidgets();
}

void ToolDialog::reAssignUIWidgets()
{
    //Use last() to choose the newest widgets.
    ui->optionWidget = ui->optionLayout->parentWidget()->findChildren<ToolOptionWidget*>(QString(), Qt::FindDirectChildrenOnly).last();
    Q_ASSERT(ui->optionWidget);
    ui->otoSaveWidget = ui->rootLayout->parentWidget()->findChildren<OtoFileSaveWidget*>(QString(), Qt::FindDirectChildrenOnly).last();
    Q_ASSERT(ui->otoSaveWidget);
}

ToolDialog::~ToolDialog()
{
    delete ui;
}

void ToolDialog::otoFileLoaded()
{
    ui->optionGroupBox->setEnabled(true);
    //ui->optionWidget->setEnabled(true);
    Q_ASSERT(ui->optionWidget->isEnabled());
    ui->otoSaveWidget->setEnabled(true);
}

void ToolDialog::ToolDialog::accept()
{
    if (adapter->doWork(ui->otoLoadWidget, ui->otoSaveWidget, ui->optionWidget, this))
        QDialog::accept();
}
