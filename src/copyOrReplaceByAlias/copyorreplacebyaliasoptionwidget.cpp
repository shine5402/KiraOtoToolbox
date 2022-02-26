#include "copyorreplacebyaliasoptionwidget.h"
#include "qstringliteral.h"
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

    connect(ui->behaviorButtonGroup, &QButtonGroup::idToggled, this, [this](){
        auto curr = ui->matchStrategyComboBox->currentIndex();
        ui->matchStrategyComboBox->clear();
        if (ui->behaviorCopyRadioButton->isChecked()){
            ui->matchStrategyComboBox->addItems({QStringLiteral("Match first then stop"),
                                                 QStringLiteral("Match all and replace all matches"),
                                                 QStringLiteral("Match all in parallel and copy all matches (copy mode only)")});
            ui->matchStrategyComboBox->setCurrentIndex(curr);
        }
        if (ui->behaviorReplaceRadioButton->isChecked()){
            ui->matchStrategyComboBox->addItems({QStringLiteral("Match first then stop"),
                                                 QStringLiteral("Match all and replace all matches")});
            ui->matchStrategyComboBox->setCurrentIndex(curr < 2 ? curr : 0);
        }

    });
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
    options.setOption("opStrategy", ui->matchStrategyComboBox->currentIndex());

    return options;
}

void CopyOrReplaceByAliasOptionWidget::setOptions(const OptionContainer& options)
{
    ui->rulesWidget->setRules(options.getOption("rules").value<QVector<ReplaceRule>>());
    ui->behaviorCopyRadioButton->setChecked(options.getOption("behaviorCopy", false).toBool());
    ui->behaviorReplaceRadioButton->setChecked(options.getOption("behaviorReplace", true).toBool());
    ui->matchStrategyComboBox->setCurrentIndex(options.getOption("opStrategy").toInt());
}

QJsonObject CopyOrReplaceByAliasOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject json;

    auto rules = options.getOption("rules").value<QVector<ReplaceRule>>();
    auto ruleJsonArray = ReplaceRule::rulesToJson(rules);
    json.insert("rules", ruleJsonArray);
    json.insert("behaviorCopy", options.getOption("behaviorCopy").toBool());
    json.insert("behaviorReplace", options.getOption("behaviorReplace").toBool());
    json.insert("opStrategy", options.getOption("opStrategy").toInt());

    return json;
}

OptionContainer CopyOrReplaceByAliasOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;

    auto ruleJsonArray = json.value("rules").toArray();
    auto rules = ReplaceRule::jsonToRules(ruleJsonArray);
    options.setOption("rules", QVariant::fromValue(rules));
    options.setOption("behaviorCopy", json.value("behaviorCopy").toBool(false));
    options.setOption("behaviorReplace", json.value("behaviorReplace").toBool(true));
    options.setOption("opStrategy", json.value("opStrategy").toInt());

    return options;
}

int CopyOrReplaceByAliasOptionWidget::optionJsonVersion() const
{
    return 2;
}


QJsonObject CopyOrReplaceByAliasOptionWidget::updateOptionJsonFrom(int version, const QJsonObject& json) const
{
    auto result = json;
    if (version == 1){
        result.insert("opStrategy", 1);//Match all and replace all matches, in nightly 20220212
    }
    return result;
}
