#include "overlapbatchsetdialogoptionwidget.h"
#include "ui_overlapbatchsetdialogoptionwidget.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

OverlapBatchSetDialogOptionWidget::OverlapBatchSetDialogOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::OverlapBatchSetDialogOptionWidget)
{
    ui->setupUi(this);
}


OverlapBatchSetDialogOptionWidget::~OverlapBatchSetDialogOptionWidget()
{
    delete ui;
}

OptionContainer OverlapBatchSetDialogOptionWidget::getOptions() const
{
    OptionContainer options;

    options.setOption("ifSetOverlapStartWith", ui->setStartWithCheckBox->isChecked());
    options.setOption("overlapStartWith", ui->setStartWithSpinBox->value());
    options.setOption("startWithPatternList", ui->setStartWithListWidget->getData());
    options.setOption("ifMatchStartOto", ui->matchStartOtoCheckBox->isChecked());
    options.setOption("makeOneThird", ui->OneThirdCheckBox->isChecked());
    return options;
}

void OverlapBatchSetDialogOptionWidget::setOptions(const OptionContainer& options)
{
    ui->setStartWithCheckBox->setChecked(options.getOption("ifSetOverlapStartWith").toBool());
    ui->setStartWithSpinBox->setValue(options.getOption("overlapStartWith").toDouble());

    ui->setStartWithListWidget->setData(options.getOption("startWithPatternList").toStringList());

    ui->matchStartOtoCheckBox->setChecked(options.getOption("ifMatchStartOto").toBool());
    ui->OneThirdCheckBox->setChecked(options.getOption("makeOneThird").toBool());
}


