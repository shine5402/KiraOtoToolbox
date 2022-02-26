#include "removeduplicateoptionwidget.h"
#include "ui_removeduplicateoptionwidget.h"

RemoveDuplicateOptionWidget::RemoveDuplicateOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::RemoveDuplicateOptionWidget)
{
    ui->setupUi(this);

    connect(ui->maxSpinBox, qOverload<int>(&QSpinBox::valueChanged), this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->affixRemoveWidget, &ToolOptionWidget::userSettingsChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->organizeCaseComboBox, qOverload<int>(&QComboBox::currentIndexChanged), this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->organizeCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->organizeStartFrom1CheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->considerNegativeSuffixCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->respectOriginalNumberOrderCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
}

RemoveDuplicateOptionWidget::~RemoveDuplicateOptionWidget()
{
    delete ui;
}

OptionContainer RemoveDuplicateOptionWidget::getOptions() const
{
    OptionContainer options;

    options.combine(ui->affixRemoveWidget->getOptions(), "affixRemove/");
    options.setOption("maxDuplicateCount", ui->maxSpinBox->value());
    options.setOption("shouldOrganize", ui->organizeCheckBox->isChecked());
    options.setOption("organizeStartFrom1", ui->organizeStartFrom1CheckBox->isChecked());
    options.setOption("pitchCaseOrganized", ui->organizeCaseComboBox->currentIndex() == 0 ? OtoEntryFunctions::Upper : OtoEntryFunctions::Lower);
    options.setOption("considerNegativeSuffix", ui->considerNegativeSuffixCheckBox->isChecked());
    options.setOption("respectOriginalNumberOrder", ui->respectOriginalNumberOrderCheckBox->isChecked());

    return options;
}

void RemoveDuplicateOptionWidget::setOptions(const OptionContainer& options)
{
    ui->affixRemoveWidget->setOptions(options.extract("affixRemove"));
    ui->maxSpinBox->setValue(options.getOption("maxDuplicateCount").toInt());
    ui->organizeCheckBox->setChecked(options.getOption("shouldOrganize").toBool());
    ui->organizeStartFrom1CheckBox->setChecked(options.getOption("organizeStartFrom1").toBool());
    ui->organizeCaseComboBox->setCurrentIndex(options.getOption("pitchCaseOrganized").toInt() == OtoEntryFunctions::Upper ? 0 : 1);
    ui->considerNegativeSuffixCheckBox->setChecked(options.getOption("considerNegativeSuffix").toBool());
    ui->respectOriginalNumberOrderCheckBox->setChecked(options.getOption("respectOriginalNumberOrder").toBool());
}


QJsonObject RemoveDuplicateOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject jsonObj;
    jsonObj.insert("affixRemove_", ui->affixRemoveWidget->optionsToJson(options.extract("affixRemove")));
    jsonObj.insert("maxDuplicateCount", options.getOption("maxDuplicateCount").toInt());
    jsonObj.insert("shouldOrganize", options.getOption("shouldOrganize").toBool());
    jsonObj.insert("organizeStartFrom1", options.getOption("organizeStartFrom1").toBool());
    jsonObj.insert("pitchCaseOrganized", options.getOption("pitchCaseOrganized").toInt());
    jsonObj.insert("considerNegativeSuffix", options.getOption("considerNegativeSuffix").toBool());
    jsonObj.insert("respectOriginalNumberOrder", options.getOption("respectOriginalNumberOrder").toBool());
    return jsonObj;
}

OptionContainer RemoveDuplicateOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;
    options.combine(ui->affixRemoveWidget->jsonToOptions(json.value("affixRemove_").toObject()), "affixRemove/");
    options.setOption("maxDuplicateCount", json.value("maxDuplicateCount").toInt());
    options.setOption("shouldOrganize", json.value("shouldOrganize").toBool());
    options.setOption("organizeStartFrom1", json.value("organizeStartFrom1").toBool());
    options.setOption("pitchCaseOrganized", json.value("pitchCaseOrganized").toInt());
    options.setOption("considerNegativeSuffix", json.value("considerNegativeSuffix").toBool());
    options.setOption("respectOriginalNumberOrder", json.value("respectOriginalNumberOrder").toBool());
    return options;
}

int RemoveDuplicateOptionWidget::optionJsonVersion() const
{
    return 1;
}
