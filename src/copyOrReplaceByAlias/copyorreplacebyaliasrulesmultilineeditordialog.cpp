#include "copyorreplacebyaliasrulesmultilineeditordialog.h"
#include "ui_copyorreplacebyaliasrulesmultilineeditordialog.h"
#include <QScrollBar>
#include <kira/lib_helper/fplus_qt_adapter.h>
#include <QMessageBox>

CopyOrReplaceByAliasRulesMultiLineEditorDialog::CopyOrReplaceByAliasRulesMultiLineEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CopyOrReplaceByAliasRulesMultiLineEditorDialog)
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

CopyOrReplaceByAliasRulesMultiLineEditorDialog::~CopyOrReplaceByAliasRulesMultiLineEditorDialog()
{
    delete ui;
}

QVector<CopyOrReplaceByAliasRule> CopyOrReplaceByAliasRulesMultiLineEditorDialog::rules() const
{
    auto matchData = ui->matchPatternEdit->toPlainText().split("\n");
    auto targetData = ui->targetPatternEdit->toPlainText().split("\n");
    auto strategyData = ui->strategyEdit->toPlainText().split("\n");

    if (!isValid())
        return {};

    QVector<CopyOrReplaceByAliasRule> result;
    auto getStrategy = [](const QString& str)->CopyOrReplaceByAliasRule::MatchStrategy{
        if (str == "e")
            return CopyOrReplaceByAliasRule::Exact;
        else if (str == "p")
            return CopyOrReplaceByAliasRule::Partial;
        else if (str == "r")
            return CopyOrReplaceByAliasRule::Regex;
        else
            Q_UNREACHABLE();
    };
    for (auto i = 0; i < matchData.count(); ++i){
        result.append({matchData.at(i), targetData.at(i), getStrategy(strategyData.at(i))});
    }
    return result;
}

void CopyOrReplaceByAliasRulesMultiLineEditorDialog::setRules(QVector<CopyOrReplaceByAliasRule> rules)
{
    ui->matchPatternEdit->setPlainText(fplus::transform([](const CopyOrReplaceByAliasRule& rule)->QString{
        return rule.matchPattern();
    }, rules).toList().join("\n"));
    ui->targetPatternEdit->setPlainText(fplus::transform([](const CopyOrReplaceByAliasRule& rule)->QString{
        return rule.targetPattern();
    }, rules).toList().join("\n"));
    ui->strategyEdit->setPlainText(fplus::transform([](const CopyOrReplaceByAliasRule& rule)->QString{
        switch (rule.strategy())
        {
            case CopyOrReplaceByAliasRule::Exact: return "e";
            case CopyOrReplaceByAliasRule::Partial: return "p";
            case CopyOrReplaceByAliasRule::Regex: return "r";
        }
        Q_UNREACHABLE();
    }, rules).toList().join("\n"));
}

bool CopyOrReplaceByAliasRulesMultiLineEditorDialog::isValid() const
{
    auto matchData = ui->matchPatternEdit->toPlainText().split("\n");
    auto targetData = ui->targetPatternEdit->toPlainText().split("\n");
    auto strategyData = ui->strategyEdit->toPlainText().split("\n");

    if (fplus::unique(QVector{matchData.count(), targetData.count(), strategyData.count()}).count() != 1)
        return false;
    if (!fplus::reduce([](bool lhs, bool rhs)->bool{
                      return lhs && rhs;
}, true,fplus::transform([](const QString& str)->bool{
                    return QStringList{"e", "p", "r"}.contains(str);
}, strategyData)))
        return false;

    return true;
}


void CopyOrReplaceByAliasRulesMultiLineEditorDialog::accept()
{
    if (!isValid()){
        QMessageBox::critical(this, {}, tr("The given data is invalid.\nIt may be caused by not identical line count or invalid strategy string.\nPlease check and try again."));
        return;
    }
    return QDialog::accept();
}
