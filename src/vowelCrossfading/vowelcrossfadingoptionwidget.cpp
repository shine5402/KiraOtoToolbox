#include "vowelcrossfadingoptionwidget.h"
#include "ui_vowelcrossfadingoptionwidget.h"

VowelCrossfadingOptionWidget::VowelCrossfadingOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::VowelCrossfadingOptionWidget)
{
    ui->setupUi(this);

    connect(ui->CVStringListModifyWidget, &StringListModifyWidget::dataModified, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->VStringListModifyWidget, &StringListModifyWidget::dataModified, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->LongRecordingPatternStringListModifyWidget, &StringListModifyWidget::dataModified, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->doCVCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->CVpreutteranceSpinBox, &QDoubleSpinBox::textChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->CVoverlapSpinBox, &QDoubleSpinBox::textChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->CVBehavoirButtonGroup, &QButtonGroup::idToggled, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->doVVOverlapIncreaseCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->removeNumberSuffixWhenMatchingCheckBox, &QCheckBox::stateChanged, this, &ToolOptionWidget::userSettingsChanged);
}

VowelCrossfadingOptionWidget::~VowelCrossfadingOptionWidget()
{
    delete ui;
}


OptionContainer VowelCrossfadingOptionWidget::getOptions() const
{
    OptionContainer options;

    options.setOption("CVList", ui->CVStringListModifyWidget->getData());
    options.setOption("VList", ui->VStringListModifyWidget->getData());
    options.setOption("longRecordingPattern", ui->LongRecordingPatternStringListModifyWidget->getData());
    options.setOption("doCVCrossfading", ui->doCVCheckBox->isChecked());
    options.setOption("CVPreUtterance", ui->CVpreutteranceSpinBox->value());
    options.setOption("CVOverlap", ui->CVoverlapSpinBox->value());
    options.setOption("CVBehaviourOverride", ui->overrideRadioButton->isChecked());
    options.setOption("CVBehaviourCopy", ui->copyRadioButton->isChecked());
    options.setOption("VVOverlapIncrease", ui->doVVOverlapIncreaseCheckBox->isChecked());
    options.setOption("removeNumberSuffixWhenMatching", ui->removeNumberSuffixWhenMatchingCheckBox->isChecked());

    return options;
}

void VowelCrossfadingOptionWidget::setOptions(const OptionContainer& options)
{
    ui->CVStringListModifyWidget->setData(options.getOption("CVList").toStringList());
    ui->VStringListModifyWidget->setData(options.getOption("VList").toStringList());
    ui->LongRecordingPatternStringListModifyWidget->setData(options.getOption("longRecordingPattern").toStringList());
    ui->doCVCheckBox->setChecked(options.getOption("doCVCrossfading").toBool());
    ui->CVpreutteranceSpinBox->setValue(options.getOption("CVPreUtterance").toDouble());
    ui->CVoverlapSpinBox->setValue(options.getOption("CVOverlap").toDouble());
    ui->overrideRadioButton->setChecked(options.getOption("CVBehaviourOverride").toBool());
    ui->copyRadioButton->setChecked(options.getOption("CVBehaviourCopy").toBool());
    ui->doVVOverlapIncreaseCheckBox->setChecked(options.getOption("VVOverlapIncrease").toBool());
    ui->removeNumberSuffixWhenMatchingCheckBox->setChecked(options.getOption("removeNumberSuffixWhenMatching").toBool());
}

QJsonObject VowelCrossfadingOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject json;

    json.insert("CVList", QJsonArray::fromStringList(options.getOption("CVList").toStringList()));
    json.insert("VList", QJsonArray::fromStringList(options.getOption("VList").toStringList()));
    json.insert("longRecordingPattern", QJsonArray::fromStringList(options.getOption("longRecordingPattern").toStringList()));
    json.insert("doCVCrossfading", options.getOption("doCVCrossfading").toBool());
    json.insert("CVPreUtterance", options.getOption("CVPreUtterance").toDouble());
    json.insert("CVOverlap", options.getOption("CVOverlap").toDouble());
    json.insert("CVBehaviourOverride", options.getOption("CVBehaviourOverride").toBool());
    json.insert("CVBehaviourCopy", options.getOption("CVBehaviourCopy").toBool());
    json.insert("VVOverlapIncrease", options.getOption("VVOverlapIncrease").toBool());
    json.insert("removeNumberSuffixWhenMatching", options.getOption("removeNumberSuffixWhenMatching").toBool());

    return json;
}

OptionContainer VowelCrossfadingOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;

    options.setOption("CVList", getStringListFromJSONObject(json, "CVList"));
    options.setOption("VList", getStringListFromJSONObject(json, "VList"));
    options.setOption("longRecordingPattern", getStringListFromJSONObject(json, "longRecordingPattern"));
    options.setOption("doCVCrossfading", json.value("doCVCrossfading").toBool());
    options.setOption("CVPreUtterance", json.value("CVPreUtterance").toDouble());
    options.setOption("CVOverlap", json.value("CVOverlap").toDouble());
    options.setOption("CVBehaviourOverride", json.value("CVBehaviourOverride").toBool());
    options.setOption("CVBehaviourCopy", json.value("CVBehaviourCopy").toBool());
    options.setOption("VVOverlapIncrease", json.value("VVOverlapIncrease").toBool());
    options.setOption("removeNumberSuffixWhenMatching", json.value("removeNumberSuffixWhenMatching").toBool());

    return options;
}

int VowelCrossfadingOptionWidget::optionJsonVersion() const
{
    return 1;
}
