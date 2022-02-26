#include "trimaroundspecificvalueoptionwidget.h"
#include "ui_trimaroundspecificvalueoptionwidget.h"

TrimAroundSpecificValueOptionWidget::TrimAroundSpecificValueOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::TrimAroundSpecificValueOptionWidget)
{
    ui->setupUi(this);

    connect(ui->fieldComboBox, &QComboBox::currentTextChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->targetValueSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->roundingRangeSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ToolOptionWidget::userSettingsChanged);
}

TrimAroundSpecificValueOptionWidget::~TrimAroundSpecificValueOptionWidget()
{
    delete ui;
}


OptionContainer TrimAroundSpecificValueOptionWidget::getOptions() const
{
    OptionContainer options;

    options.setOption("field", ui->fieldComboBox->currentIndex() + 2);//For filename and alias
    options.setOption("targetValue", ui->targetValueSpinBox->value());
    options.setOption("roundingRange", ui->roundingRangeSpinBox->value());

    return options;
}

void TrimAroundSpecificValueOptionWidget::setOptions(const OptionContainer& options)
{
    ui->fieldComboBox->setCurrentIndex(options.getOption("field", 2).toInt() - 2);
    ui->targetValueSpinBox->setValue(options.getOption("targetValue").toDouble());
    ui->roundingRangeSpinBox->setValue(options.getOption("roundingRange").toDouble());
}

QJsonObject TrimAroundSpecificValueOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject json;

    json.insert("field", options.getOption("field").toInt());
    json.insert("targetValue", options.getOption("targetValue").toDouble());
    json.insert("roundingRange", options.getOption("roundingRange").toDouble());

    return json;
}

OptionContainer TrimAroundSpecificValueOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;

    options.setOption("field", json.value("field").toInt());
    options.setOption("targetValue", json.value("targetValue").toDouble());
    options.setOption("roundingRange", json.value("roundingRange").toDouble());

    return options;
}

int TrimAroundSpecificValueOptionWidget::optionJsonVersion() const
{
    return 1;
}
