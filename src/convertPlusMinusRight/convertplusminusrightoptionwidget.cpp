#include "convertplusminusrightoptionwidget.h"
#include "ui_convertplusminusrightoptionwidget.h"

ConvertPlusMinusRightOptionWidget::ConvertPlusMinusRightOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::ConvertPlusMinusRightOptionWidget)
{
    ui->setupUi(this);

    connect(ui->buttonGroup, &QButtonGroup::idToggled, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->interpretBySystemEncodingCheckBox, &QCheckBox::toggled, this, &ToolOptionWidget::userSettingsChanged);
}

ConvertPlusMinusRightOptionWidget::~ConvertPlusMinusRightOptionWidget()
{
    delete ui;
}

OptionContainer ConvertPlusMinusRightOptionWidget::getOptions() const
{
    OptionContainer options;

    Q_ASSERT(ui->positiveRadioButton->isChecked() ^ ui->negativeRadioButton->isChecked());

    options.setOption("savePositive", ui->positiveRadioButton->isChecked());
    options.setOption("saveNegative", ui->negativeRadioButton->isChecked());
    options.setOption("interpretBySystemEncoding", ui->interpretBySystemEncodingCheckBox->isChecked());

    return options;
}

void ConvertPlusMinusRightOptionWidget::setOptions(const OptionContainer& options)
{
    ui->positiveRadioButton->setChecked(options.getOption("savePositive").toBool());
    ui->negativeRadioButton->setChecked(options.getOption("saveNegative").toBool());
    ui->interpretBySystemEncodingCheckBox->setChecked(options.getOption("interpretBySystemEncoding").toBool());
}

QJsonObject ConvertPlusMinusRightOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject json;

    json.insert("savePositive", options.getOption("savePositive").toBool());
    json.insert("saveNegative", options.getOption("saveNegative").toBool());
    json.insert("interpretBySystemEncoding", options.getOption("interpretBySystemEncoding").toBool());

    return json;
}

OptionContainer ConvertPlusMinusRightOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;

    options.setOption("savePositive", json.value("savePositive").toBool());
    options.setOption("saveNegative", json.value("saveNegative").toBool());
    options.setOption("interpretBySystemEncoding", json.value("interpretBySystemEncoding").toBool());

    return options;
}

int ConvertPlusMinusRightOptionWidget::optionJsonVersion() const
{
    return 1;
}
