#include "replacefilenameoptionwidget.h"
#include "ui_replacefilenameoptionwidget.h"

ReplaceFileNameOptionWidget::ReplaceFileNameOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::ReplaceFileNameOptionWidget)
{
    ui->setupUi(this);

    connect(ui->rulesWidget, &ReplaceRulesWidget::rulesChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->interpretBySystemEncodingCheckBox, &QCheckBox::toggled, this, &ToolOptionWidget::userSettingsChanged);
}

ReplaceFileNameOptionWidget::~ReplaceFileNameOptionWidget()
{
    delete ui;
}


OptionContainer ReplaceFileNameOptionWidget::getOptions() const
{
    OptionContainer options;

    options.setOption("rules", QVariant::fromValue(ui->rulesWidget->getRules()));
    options.setOption("interpretBySystemEncoding", ui->interpretBySystemEncodingCheckBox->isChecked());

    return options;
}

void ReplaceFileNameOptionWidget::setOptions(const OptionContainer& options)
{
    ui->rulesWidget->setRules(options.getOption("rules").value<QVector<ReplaceRule>>());
    ui->interpretBySystemEncodingCheckBox->setChecked(options.getOption("interpretBySystemEncoding").toBool());
}

QJsonObject ReplaceFileNameOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject json;

    auto rules = options.getOption("rules").value<QVector<ReplaceRule>>();
    auto ruleJsonArray = ReplaceRule::rulesToJson(rules);
    json.insert("rules", ruleJsonArray);
    json.insert("interpretBySystemEncoding", options.getOption("interpretBySystemEncoding").toBool());

    return json;
}

OptionContainer ReplaceFileNameOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;

    auto ruleJsonArray = json.value("rules").toArray();
    auto rules = ReplaceRule::jsonToRules(ruleJsonArray);
    options.setOption("interpretBySystemEncoding", json.value("interpretBySystemEncoding").toBool());
    options.setOption("rules", QVariant::fromValue(rules));

    return options;
}

int ReplaceFileNameOptionWidget::optionJsonVersion() const
{
    return 1;
}
