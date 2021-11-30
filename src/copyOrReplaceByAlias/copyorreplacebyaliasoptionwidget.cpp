#include "copyorreplacebyaliasoptionwidget.h"
#include "ui_copyorreplacebyaliasoptionwidget.h"
#include "copyorreplacebyaliasrulesmodel.h"
#include "copyorreplacebyaliasrulesdelegate.h"
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "copyorreplacebyaliasrulesmultilineeditordialog.h"

CopyOrReplaceByAliasOptionWidget::CopyOrReplaceByAliasOptionWidget(QWidget *parent) :
    ToolOptionWidget(parent),
    ui(new Ui::CopyOrReplaceByAliasOptionWidget)
{
    ui->setupUi(this);

    model = new CopyOrReplaceByAliasRulesModel(this);
    auto delegate = new CopyOrReplaceByAliasRulesDelegate(this);
    ui->ruleTableView->setModel(model);
    ui->ruleTableView->setItemDelegate(delegate);

    connect(ui->addButton, &QPushButton::clicked, this, &CopyOrReplaceByAliasOptionWidget::addRule);
    connect(ui->deleteButton, &QPushButton::clicked, this, &CopyOrReplaceByAliasOptionWidget::removeRule);
    connect(ui->multiLineEditButton, &QPushButton::clicked, this, &CopyOrReplaceByAliasOptionWidget::multiLineEdit);

    connect(model, &QAbstractItemModel::dataChanged, this, &ToolOptionWidget::userSettingsChanged);
    connect(ui->behaviorButtonGroup, &QButtonGroup::idToggled, this, &ToolOptionWidget::userSettingsChanged);
}


CopyOrReplaceByAliasOptionWidget::~CopyOrReplaceByAliasOptionWidget()
{
    delete ui;
}

void CopyOrReplaceByAliasOptionWidget::addRule()
{
    auto dialog = new QDialog(this);

    auto formLayout = new QFormLayout;
    auto matchPatternEdit = new QLineEdit(dialog);
    formLayout->addRow(tr("Matching pattern"), matchPatternEdit);
    auto targetPatternEdit = new QLineEdit(dialog);
    formLayout->addRow(tr("Replacing target"), targetPatternEdit);
    auto strategyComboBox = new QComboBox(dialog);
    strategyComboBox->addItems({
                                   CopyOrReplaceByAliasRule::getStrategyString(CopyOrReplaceByAliasRule::Exact),
                                   CopyOrReplaceByAliasRule::getStrategyString(CopyOrReplaceByAliasRule::Partial),
                                   CopyOrReplaceByAliasRule::getStrategyString(CopyOrReplaceByAliasRule::Regex)
                               });
    formLayout->addRow(tr("Matching strategy"), strategyComboBox);

    auto label = new QLabel(tr("Specify details of the new rule below."), dialog);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, dialog);
    connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);

    auto rootLayout = new QVBoxLayout(dialog);
    rootLayout->addWidget(label);
    rootLayout->addLayout(formLayout);
    rootLayout->addWidget(buttonBox);

    auto ok = dialog->exec();
    if (ok == QDialog::Accepted){
        model->appendRule({matchPatternEdit->text(), targetPatternEdit->text(),
                           (CopyOrReplaceByAliasRule::MatchStrategy) strategyComboBox->currentIndex()});
        emit userSettingsChanged();
    }
}

void CopyOrReplaceByAliasOptionWidget::removeRule()
{
    if (model->getRules().isEmpty())
        return;

    auto currentRule = model->getRules().at(ui->ruleTableView->currentIndex().row());
    auto reply = QMessageBox::question(this, {}, tr("<p>Are you sure to remove current rule?</p>"
"<p>Matching pattern: %1<br>Replacing target: %2<br>Strategy: %3</p>").arg(currentRule.matchPattern(), currentRule.targetPattern(), CopyOrReplaceByAliasRule::getStrategyString(currentRule.strategy())));
    if (reply == QMessageBox::Yes){
        model->removeRule(ui->ruleTableView->currentIndex().row());
        emit userSettingsChanged();
    }
}

void CopyOrReplaceByAliasOptionWidget::multiLineEdit()
{
    auto dialog = new CopyOrReplaceByAliasRulesMultiLineEditorDialog(this);
    dialog->setRules(model->getRules());
    auto reply = dialog->exec();
    if (reply == QDialog::Accepted)
    {
        model->setRules(dialog->rules());
        emit userSettingsChanged();
    }
    dialog->deleteLater();
}


OptionContainer CopyOrReplaceByAliasOptionWidget::getOptions() const
{
    OptionContainer options;

    options.setOption("rules", QVariant::fromValue(model->getRules()));
    options.setOption("behaviorCopy", ui->behaviorCopyRadioButton->isChecked());
    options.setOption("behaviorReplace", ui->behaviorReplaceRadioButton->isChecked());

    return options;
}

void CopyOrReplaceByAliasOptionWidget::setOptions(const OptionContainer& options)
{
    model->setRules(options.getOption("rules").value<QVector<CopyOrReplaceByAliasRule>>());
    ui->behaviorCopyRadioButton->setChecked(options.getOption("behaviorCopy").toBool());
    ui->behaviorReplaceRadioButton->setChecked(options.getOption("behaviorReplace").toBool());
}

QJsonArray arrayFromJsonValueVector(QVector<QJsonValue> vector){
    QJsonArray array;
    for (const auto& i : qAsConst(vector))
    {
        array.append(i);
    }
    return array;
}

QJsonObject CopyOrReplaceByAliasOptionWidget::optionsToJson(const OptionContainer& options) const
{
    QJsonObject json;

    auto rules = options.getOption("rules").value<QVector<CopyOrReplaceByAliasRule>>();
    auto ruleJsonArray = arrayFromJsonValueVector(fplus::transform([](const CopyOrReplaceByAliasRule& rule)->QJsonValue{
        QJsonObject ruleJson;
        ruleJson.insert("matchPattern", rule.matchPattern());
        ruleJson.insert("targetPattern", rule.targetPattern());
        ruleJson.insert("strategy", rule.strategy());
        return ruleJson;
    }, rules));
    json.insert("rules", ruleJsonArray);
    json.insert("behaviorCopy", options.getOption("behaviorCopy").toBool());
    json.insert("behaviorReplace", options.getOption("behaviorReplace").toBool());

    return json;
}

OptionContainer CopyOrReplaceByAliasOptionWidget::jsonToOptions(const QJsonObject& json) const
{
    OptionContainer options;

    auto ruleJsonArray = json.value("rules").toArray();
    auto rules = fplus::transform([](const QJsonValue& value)->CopyOrReplaceByAliasRule{
        auto obj = value.toObject();
        CopyOrReplaceByAliasRule rule;
        rule.setMatchPattern(obj.value("matchPattern").toString());
        rule.setTargetPattern(obj.value("targetPattern").toString());
        rule.setStrategy((CopyOrReplaceByAliasRule::MatchStrategy) obj.value("strategy").toInt());
        return rule;
    }, ruleJsonArray);
    options.setOption("rules", QVariant::fromValue(rules));
    options.setOption("behaviorCopy", json.value("behaviorCopy").toBool());
    options.setOption("behaviorReplace", json.value("behaviorReplace").toBool());

    return options;
}

int CopyOrReplaceByAliasOptionWidget::optionJsonVersion() const
{
    return 1;
}
