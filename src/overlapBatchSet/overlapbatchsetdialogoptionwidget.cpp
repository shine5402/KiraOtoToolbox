#include "overlapbatchsetdialogoptionwidget.h"
#include "ui_overlapbatchsetdialogoptionwidget.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <kira/lib_helper/fplus_qt_adapter.h>
#include <QSpinBox>

OverlapBatchSetDialogOptionWidget::OverlapBatchSetDialogOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::OverlapBatchSetDialogOptionWidget)
{
    ui->setupUi(this);

    connect(ui->setStartWithCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->setStartWithSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->oneThirdCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->matchStartOtoCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->setStartWithListWidget, &StringListModifyWidget::dataModified, this, &ToolOptionWidget::userSettingsChanged);
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
    options.setOption("makeOneThird", ui->oneThirdCheckBox->isChecked());
    return options;
}

void OverlapBatchSetDialogOptionWidget::setOptions(const OptionContainer& options)
{
    ui->setStartWithCheckBox->setChecked(options.getOption("ifSetOverlapStartWith").toBool());
    ui->setStartWithSpinBox->setValue(options.getOption("overlapStartWith").toDouble());

    ui->setStartWithListWidget->setData(options.getOption("startWithPatternList").toStringList());

    ui->matchStartOtoCheckBox->setChecked(options.getOption("ifMatchStartOto").toBool());
    ui->oneThirdCheckBox->setChecked(options.getOption("makeOneThird").toBool());
}

QJsonObject OverlapBatchSetDialogOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject jsonObj;

    jsonObj.insert("ifSetOverlapStartWith", options.getOption("ifSetOverlapStartWith").toBool());
    jsonObj.insert("overlapStartWith", options.getOption("overlapStartWith").toDouble());
    jsonObj.insert("startWithPatternList", QJsonArray::fromStringList(options.getOption("startWithPatternList").toStringList()));
    jsonObj.insert("ifMatchStartOto", options.getOption("ifMatchStartOto").toBool());
    jsonObj.insert("makeOneThird", options.getOption("makeOneThird").toBool());

    return jsonObj;
}

OptionContainer OverlapBatchSetDialogOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;

    options.setOption("ifSetOverlapStartWith", json.value("ifSetOverlapStartWith").toBool());
    options.setOption("overlapStartWith", json.value("overlapStartWith").toDouble());
    options.setOption("startWithPatternList", getStringListFromJSONObject(json, "startWithPatternList"));
    options.setOption("ifMatchStartOto", json.value("ifMatchStartOto").toBool());
    options.setOption("makeOneThird", json.value("makeOneThird").toBool());

    return options;
}

int OverlapBatchSetDialogOptionWidget::optionJsonVersion() const
{
    return 1;
}
