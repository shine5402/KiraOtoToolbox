#include "ReplaceRulesMultilineEditorDialog.h"
#include "ui_ReplaceRulesMultilineEditorDialog.h"

#include <QMessageBox>
#include <QScrollBar>

#include <algorithm>
#include <ranges>

ReplaceRulesMultiLineEditorDialog::ReplaceRulesMultiLineEditorDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::ReplaceRulesMultiLineEditorDialog)
{
    ui->setupUi(this);

    auto matchPatternScrollBar = ui->matchPatternEdit->verticalScrollBar();
    auto targetPatternScrollBar = ui->targetPatternEdit->verticalScrollBar();
    auto strategyPatternScrollBar = ui->strategyEdit->verticalScrollBar();

    connect(matchPatternScrollBar, &QScrollBar::valueChanged, targetPatternScrollBar, &QScrollBar::setValue);
    connect(matchPatternScrollBar, &QScrollBar::valueChanged, strategyPatternScrollBar, &QScrollBar::setValue);

    connect(targetPatternScrollBar, &QScrollBar::valueChanged, matchPatternScrollBar, &QScrollBar::setValue);
    connect(targetPatternScrollBar, &QScrollBar::valueChanged, strategyPatternScrollBar, &QScrollBar::setValue);

    connect(strategyPatternScrollBar, &QScrollBar::valueChanged, matchPatternScrollBar, &QScrollBar::setValue);
    connect(strategyPatternScrollBar, &QScrollBar::valueChanged, targetPatternScrollBar, &QScrollBar::setValue);
}

ReplaceRulesMultiLineEditorDialog::~ReplaceRulesMultiLineEditorDialog()
{
    delete ui;
}

QVector<ReplaceRule> ReplaceRulesMultiLineEditorDialog::rules() const
{
    auto matchData = ui->matchPatternEdit->toPlainText().split("\n");
    auto targetData = ui->targetPatternEdit->toPlainText().split("\n");
    auto strategyData = ui->strategyEdit->toPlainText().split("\n");

    if (!isValid())
        return {};

    QVector<ReplaceRule> result;
    auto getStrategy = [](const QString &str) -> ReplaceRule::MatchStrategy {
        if (str == "e")
            return ReplaceRule::Exact;
        else if (str == "p")
            return ReplaceRule::Partial;
        else if (str == "r")
            return ReplaceRule::Regex;
        else
            Q_UNREACHABLE();
    };
    for (auto i = 0; i < matchData.count(); ++i) {
        result.append({matchData.at(i), targetData.at(i), getStrategy(strategyData.at(i))});
    }
    return result;
}

void ReplaceRulesMultiLineEditorDialog::setRules(QVector<ReplaceRule> rules)
{
    auto matchPatterns =
        rules | std::views::transform([](const ReplaceRule &rule) -> QString { return rule.matchPattern(); }) |
        std::ranges::to<QStringList>();
    ui->matchPatternEdit->setPlainText(matchPatterns.join("\n"));

    auto targetPatterns =
        rules | std::views::transform([](const ReplaceRule &rule) -> QString { return rule.targetPattern(); }) |
        std::ranges::to<QStringList>();
    ui->targetPatternEdit->setPlainText(targetPatterns.join("\n"));

    auto strategies =
        rules | std::views::transform([](const ReplaceRule &rule) -> QString {
            switch (rule.strategy()) {
            case ReplaceRule::Exact:
                return "e";
            case ReplaceRule::Partial:
                return "p";
            case ReplaceRule::Regex:
                return "r";
            }
            Q_UNREACHABLE();
        }) |
        std::ranges::to<QStringList>();
    ui->strategyEdit->setPlainText(strategies.join("\n"));
}

bool ReplaceRulesMultiLineEditorDialog::isValid() const
{
    auto matchData = ui->matchPatternEdit->toPlainText().split("\n");
    auto targetData = ui->targetPatternEdit->toPlainText().split("\n");
    auto strategyData = ui->strategyEdit->toPlainText().split("\n");

    if (matchData.count() != targetData.count() || targetData.count() != strategyData.count())
        return false;
    if (!std::ranges::all_of(
            strategyData, [](const QString &str) -> bool { return QStringList{"e", "p", "r"}.contains(str); }))
        return false;

    return true;
}

void ReplaceRulesMultiLineEditorDialog::accept()
{
    if (!isValid()) {
        QMessageBox::critical(this, {},
                              tr("The given data is invalid.\nIt may be caused by not identical line count or invalid "
                                 "strategy string.\nPlease check and try again."));
        return;
    }
    return QDialog::accept();
}
