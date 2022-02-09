#include "copyorreplacebyaliasoptionwidget.h"
#include "ui_copyorreplacebyaliasoptionwidget.h"
#include "utils/misc/misc.h"
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QMessageBox>

CopyOrReplaceByAliasOptionWidget::CopyOrReplaceByAliasOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::CopyOrReplaceByAliasOptionWidget)
{
    ui->setupUi(this);

    connect(ui->rulesWidget, &ReplaceRulesWidget::rulesChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->behaviorButtonGroup, &QButtonGroup::idToggled, this, &ToolOptionWidget::userSettingsChanged);
}


CopyOrReplaceByAliasOptionWidget::~CopyOrReplaceByAliasOptionWidget()
{
    delete ui;
}

OptionContainer CopyOrReplaceByAliasOptionWidget::getOptions() const
{
    OptionContainer options;

    options.setOption("rules", QVariant::fromValue(ui->rulesWidget->getRules()));
    options.setOption("behaviorCopy", ui->behaviorCopyRadioButton->isChecked());
    options.setOption("behaviorReplace", ui->behaviorReplaceRadioButton->isChecked());

    return options;
}

void CopyOrReplaceByAliasOptionWidget::setOptions(const OptionContainer& options)
{
    ui->rulesWidget->setRules(options.getOption("rules").value<QVector<ReplaceRule>>());
    ui->behaviorCopyRadioButton->setChecked(options.getOption("behaviorCopy").toBool());
    ui->behaviorReplaceRadioButton->setChecked(options.getOption("behaviorReplace").toBool());
}

QJsonObject CopyOrReplaceByAliasOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject json;

    auto rules = options.getOption("rules").value<QVector<ReplaceRule>>();
    auto ruleJsonArray = ReplaceRule::rulesToJson(rules);
    json.insert("rules", ruleJsonArray);
    json.insert("behaviorCopy", options.getOption("behaviorCopy").toBool());
    json.insert("behaviorReplace", options.getOption("behaviorReplace").toBool());

    return json;
}

OptionContainer CopyOrReplaceByAliasOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;

    auto ruleJsonArray = json.value("rules").toArray();
    auto rules = ReplaceRule::jsonToRules(ruleJsonArray);
    options.setOption("rules", QVariant::fromValue(rules));
    options.setOption("behaviorCopy", json.value("behaviorCopy").toBool());
    options.setOption("behaviorReplace", json.value("behaviorReplace").toBool());

    return options;
}

int CopyOrReplaceByAliasOptionWidget::optionJsonVersion() const
{
    return 1;
}
