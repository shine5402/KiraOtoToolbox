#include "replaceruleswidget.h"
#include <kira/lib_helper/fplus_qt_adapter.h>
#include "replacerulesmultilineeditordialog.h"
#include "replacerulesdelegate.h"
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "ui_replaceruleswidget.h"

ReplaceRulesWidget::ReplaceRulesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReplaceRulesWidget)
{
    ui->setupUi(this);

    model = new ReplaceRulesModel(this);
    auto delegate = new ReplaceRulesDelegate(this);
    ui->ruleTableView->setModel(model);
    ui->ruleTableView->setItemDelegate(delegate);

    connect(ui->addButton, &QPushButton::clicked, this, &ReplaceRulesWidget::addRule);
    connect(ui->deleteButton, &QPushButton::clicked, this, &ReplaceRulesWidget::removeRule);
    connect(ui->multiLineEditButton, &QPushButton::clicked, this, &ReplaceRulesWidget::multiLineEdit);
    connect(ui->moveUpButton, &QPushButton::clicked, this, &ReplaceRulesWidget::moveUpRule);
    connect(ui->moveDownButton, &QPushButton::clicked, this, &ReplaceRulesWidget::moveDownRule);
    connect(ui->sortByMatchPatternLengthButton, &QPushButton::clicked, this, &ReplaceRulesWidget::sortRuleByMatchPatternLength);

    connect(model, &QAbstractItemModel::dataChanged, this, &ReplaceRulesWidget::rulesChanged);
}

ReplaceRulesWidget::~ReplaceRulesWidget()
{
    delete ui;
}

QVector<ReplaceRule> ReplaceRulesWidget::getRules() const
{
    return model->getRules();
}

void ReplaceRulesWidget::setRules(const QVector<ReplaceRule>& value)
{
    model->setRules(value);
}

void ReplaceRulesWidget::addRule()
{
    auto dialog = new QDialog(this);

    auto formLayout = new QFormLayout;
    auto matchPatternEdit = new QLineEdit(dialog);
    formLayout->addRow(tr("Matching pattern"), matchPatternEdit);
    auto targetPatternEdit = new QLineEdit(dialog);
    formLayout->addRow(tr("Replacing target"), targetPatternEdit);
    auto strategyComboBox = new QComboBox(dialog);
    strategyComboBox->addItems({
                                   ReplaceRule::getStrategyString(ReplaceRule::Exact),
                                   ReplaceRule::getStrategyString(ReplaceRule::Partial),
                                   ReplaceRule::getStrategyString(ReplaceRule::Regex)
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
                           (ReplaceRule::MatchStrategy) strategyComboBox->currentIndex()});
        emit rulesChanged();
    }
}

void ReplaceRulesWidget::removeRule()
{
    if (model->getRules().isEmpty())
        return;

    auto currentRule = model->getRules().at(ui->ruleTableView->currentIndex().row());
    auto reply = QMessageBox::question(this, {}, tr("<p>Are you sure to remove current rule?</p>"
"<p>Matching pattern: %1<br>Replacing target: %2<br>Strategy: %3</p>").arg(currentRule.matchPattern(), currentRule.targetPattern(), ReplaceRule::getStrategyString(currentRule.strategy())));
    if (reply == QMessageBox::Yes){
        model->removeRule(ui->ruleTableView->currentIndex().row());
        emit rulesChanged();
    }
}

void ReplaceRulesWidget::multiLineEdit()
{
    auto dialog = new ReplaceRulesMultiLineEditorDialog(this);
    dialog->setRules(model->getRules());
    auto reply = dialog->exec();
    if (reply == QDialog::Accepted)
    {
        model->setRules(dialog->rules());
        emit rulesChanged();
    }
    dialog->deleteLater();
}

void ReplaceRulesWidget::moveUpRule()
{
    model->moveUpRule(ui->ruleTableView->currentIndex().row());
}

void ReplaceRulesWidget::moveDownRule()
{
    model->moveDownRule(ui->ruleTableView->currentIndex().row());
}

void ReplaceRulesWidget::sortRuleByMatchPatternLength()
{
    model->setRules(fplus::sort_by([](const ReplaceRule& lhs, const ReplaceRule& rhs)->bool{
        return lhs.matchPattern().count() > rhs.matchPattern().count();
    }, model->getRules()));
}
