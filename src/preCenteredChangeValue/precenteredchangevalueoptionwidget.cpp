#include "precenteredchangevalueoptionwidget.h"
#include "ui_precenteredchangevalueoptionwidget.h"

PreCenteredChangeValueOptionWidget::PreCenteredChangeValueOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::PreCenteredChangeValueOptionWidget)
{
    ui->setupUi(this);
    connect(ui->normalizeWithTempoButton, &QPushButton::clicked, this, &PreCenteredChangeValueOptionWidget::setParamsWithUITempo);

    connect(ui->constFieldDoubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->preutteranceDoubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->overlapDoubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->rightDoubleSpinBox, qOverload<double>(&QDoubleSpinBox::valueChanged), this, &ToolOptionWidget::userSettingsChanged);
}

PreCenteredChangeValueOptionWidget::~PreCenteredChangeValueOptionWidget()
{
    delete ui;
}

void PreCenteredChangeValueOptionWidget::setParamsWithUITempo()
{
    auto tempo = ui->tempoDoubleSpinBox->value();
    auto beat = 60000 / tempo;
    ui->constFieldDoubleSpinBox->setValue(beat * 3 / 4);
    ui->preutteranceDoubleSpinBox->setValue(beat / 2);
    ui->overlapDoubleSpinBox->setValue(beat / 6);
    ui->rightDoubleSpinBox->setValue(-(beat * 7 / 6));
}

OptionContainer PreCenteredChangeValueOptionWidget::getOptions() const
{
    OptionContainer options;

    options.setOption("constField", ui->constFieldDoubleSpinBox->value());
    options.setOption("preutterance", ui->preutteranceDoubleSpinBox->value());
    options.setOption("overlap", ui->overlapDoubleSpinBox->value());
    options.setOption("right", ui->rightDoubleSpinBox->value());

    return options;
}

void PreCenteredChangeValueOptionWidget::setOptions(const OptionContainer& options)
{
    ui->constFieldDoubleSpinBox->setValue(options.getOption("constField", 375.0).toDouble());//3/4
    ui->preutteranceDoubleSpinBox->setValue(options.getOption("preutterance", 250.0).toDouble());//1/2
    ui->overlapDoubleSpinBox->setValue(options.getOption("overlap", 83.333).toDouble());//1/6
    ui->rightDoubleSpinBox->setValue(options.getOption("right", -583.333).toDouble());//all + overlap
}

QJsonObject PreCenteredChangeValueOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject json;

    json.insert("constField", options.getOption("constField").toDouble());
    json.insert("preutterance", options.getOption("preutterance").toDouble());
    json.insert("overlap", options.getOption("overlap").toDouble());
    json.insert("right", options.getOption("right").toDouble());

    return json;
}

OptionContainer PreCenteredChangeValueOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;

    options.setOption("constField", json.value("constField").toDouble(375.0));
    options.setOption("preutterance", json.value("preutterance").toDouble(250.0));
    options.setOption("overlap", json.value("overlap").toDouble(83.333));
    options.setOption("right", json.value("right").toDouble(-583.333));

    return options;
}

int PreCenteredChangeValueOptionWidget::optionJsonVersion() const
{
    return 1;
}
