#include "precenteredchangevalueoptionwidget.h"
#include "ui_precenteredchangevalueoptionwidget.h"

PreCenteredChangeValueOptionWidget::PreCenteredChangeValueOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::PreCenteredChangeValueOptionWidget)
{
    ui->setupUi(this);
    connect(ui->normalizeWithTempoButton, &QPushButton::clicked, this, &PreCenteredChangeValueOptionWidget::setParamsWithUITempo);

    connect(ui->constFieldCheckBox, &QCheckBox::toggled, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->preutteranceCheckBox, &QCheckBox::toggled, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->overlapCheckBox, &QCheckBox::toggled, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->rightCheckBox, &QCheckBox::toggled, this, &ToolOptionWidget::userSettingsChanged);
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

    options.setOption("changeConstField", ui->constFieldCheckBox->isChecked());
    options.setOption("constField", ui->constFieldDoubleSpinBox->value());
    options.setOption("changePreutterance", ui->preutteranceCheckBox->isChecked());
    options.setOption("preutterance", ui->preutteranceDoubleSpinBox->value());
    options.setOption("changeOverlap", ui->overlapCheckBox->isChecked());
    options.setOption("overlap", ui->overlapDoubleSpinBox->value());
    options.setOption("changeRight", ui->rightCheckBox->isChecked());
    options.setOption("right", ui->rightDoubleSpinBox->value());

    return options;
}

void PreCenteredChangeValueOptionWidget::setOptions(const OptionContainer& options)
{
    ui->constFieldCheckBox->setChecked(options.getOption("changeConstField", true).toBool());
    ui->constFieldDoubleSpinBox->setValue(options.getOption("constField", 375.0).toDouble());//3/4
    ui->preutteranceCheckBox->setChecked(options.getOption("changePreutterance", true).toBool());
    ui->preutteranceDoubleSpinBox->setValue(options.getOption("preutterance", 250.0).toDouble());//1/2
    ui->overlapCheckBox->setChecked(options.getOption("changeOverlap", true).toBool());
    ui->overlapDoubleSpinBox->setValue(options.getOption("overlap", 83.333).toDouble());//1/6
    ui->rightCheckBox->setChecked(options.getOption("changeRight", true).toBool());
    ui->rightDoubleSpinBox->setValue(options.getOption("right", -583.333).toDouble());//all + overlap
}

QJsonObject PreCenteredChangeValueOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject json;

    json.insert("changeConstField", options.getOption("changeConstField").toBool());
    json.insert("constField", options.getOption("constField").toDouble());
    json.insert("changePreutterance", options.getOption("changePreutterance").toBool());
    json.insert("preutterance", options.getOption("preutterance").toDouble());
    json.insert("changeOverlap", options.getOption("changeOverlap").toBool());
    json.insert("overlap", options.getOption("overlap").toDouble());
    json.insert("changeRight", options.getOption("changeRight").toBool());
    json.insert("right", options.getOption("right").toDouble());

    return json;
}

OptionContainer PreCenteredChangeValueOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;

    options.setOption("changeConstField", json.value("changeConstField").toBool(true));
    options.setOption("constField", json.value("constField").toDouble(375.0));
    options.setOption("changePreutterance", json.value("changePreutterance").toBool(true));
    options.setOption("preutterance", json.value("preutterance").toDouble(250.0));
    options.setOption("changeOverlap", json.value("changeOverlap").toBool(true));
    options.setOption("overlap", json.value("overlap").toDouble(83.333));
    options.setOption("changeRight", json.value("changeRight").toBool(true));
    options.setOption("right", json.value("right").toDouble(-583.333));

    return options;
}

int PreCenteredChangeValueOptionWidget::optionJsonVersion() const
{
    return 1;
}
