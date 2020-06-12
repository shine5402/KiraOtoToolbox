#include "removeduplicatedialog.h"
#include "ui_removeduplicatedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include "otofilereader.h"
#include "utils/dialogs/showotolistdialog.h"
#include <QInputDialog>
#include "utils/models/otolistaliasshowchangemodel.h"
#include <algorithm>
#include "utils/widgets/otofilesavewidget.h"
#include "removeduplicatedialogoptionwidget.h"
#ifdef SHINE5402OTOBOX_TEST
#include <QTimer>
#endif

RemoveDuplicateDialog::RemoveDuplicateDialog(ToolDialogAdapter* adapter, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveDuplicateDialog),
    adapter(adapter)
{
    ui->setupUi(this);
    connect(ui->otoLoadWidget, &OtoFileLoadWidget::loaded, this, &RemoveDuplicateDialog::otoFileLoaded);
    adapter->setupSpecificUIWidgets(ui->rootLayout);
    reAssignUIWidgets();
}

void RemoveDuplicateDialog::reAssignUIWidgets()
{
    //Use last() to choose the newest widgets.
    ui->optionWidget = ui->optionLayout->parentWidget()->findChildren<ToolOptionWidget*>(QString(), Qt::FindDirectChildrenOnly).last();
    Q_ASSERT(ui->optionWidget);
    ui->otoSaveWidget = ui->rootLayout->parentWidget()->findChildren<OtoFileSaveWidget*>(QString(), Qt::FindDirectChildrenOnly).last();
    Q_ASSERT(ui->otoSaveWidget);
}

RemoveDuplicateDialog::~RemoveDuplicateDialog()
{
    delete ui;
}

void RemoveDuplicateDialog::otoFileLoaded()
{
    ui->optionGroupBox->setEnabled(true);
    ui->otoSaveWidget->setEnabled(true);
}

void RemoveDuplicateDialog::RemoveDuplicateDialog::accept()
{
    adapter->doWork(ui->otoLoadWidget, ui->otoSaveWidget, ui->optionWidget, this);
    QDialog::accept();
}
