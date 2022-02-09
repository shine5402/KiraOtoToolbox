#include "replacerule.h"
#include <kira/lib_helper/fplus_qt_adapter.h>
#include "utils/misc/misc.h"
#include "qjsonarray.h"
#include <QRegularExpression>

ReplaceRule::ReplaceRule(QString matchPattern, QString targetPattern,
                                                   ReplaceRule::MatchStrategy strategy):
    matchPattern_(std::move(matchPattern)), targetPattern_(std::move(targetPattern))
{
    this->strategy_ = strategy;
}

ReplaceRule::ReplaceRule()
{

}

QString ReplaceRule::matchPattern() const
{
    return matchPattern_;
}

void ReplaceRule::setMatchPattern(const QString& value)
{
    matchPattern_ = value;
}

QString ReplaceRule::targetPattern() const
{
    return targetPattern_;
}

void ReplaceRule::setTargetPattern(const QString& value)
{
    targetPattern_ = value;
}

ReplaceRule::MatchStrategy ReplaceRule::strategy() const
{
    return strategy_;
}

void ReplaceRule::setStrategy(const MatchStrategy& value)
{
    strategy_ = value;
}

QString ReplaceRule::getStrategyString(ReplaceRule::MatchStrategy strategy)
{
    switch (strategy) {
        case ReplaceRule::Exact:return tr("Exact");
        case ReplaceRule::Partial:return tr("Partial");
        case ReplaceRule::Regex:return tr("Regex");
    }
    return {};
}

bool ReplaceRule::operator==(const ReplaceRule& other) const
{
    return matchPattern() == other.matchPattern() && targetPattern() == other.targetPattern() && strategy() == other.strategy();
}

bool ReplaceRule::match(const QString& alias) const
{
    switch (strategy()){
        case ReplaceRule::Exact:return matchPattern().compare(alias) == 0;
        case ReplaceRule::Partial:return alias.contains(matchPattern());
        case ReplaceRule::Regex:return QRegularExpression{matchPattern()}.match(alias).hasMatch();
    }
    Q_UNREACHABLE();
}

QString ReplaceRule::replace(const QString& alias) const
{
    if (!match(alias))
        return alias;
    switch (strategy()){
        case ReplaceRule::Exact: [[fallthrough]];
        case ReplaceRule::Partial:return QString(alias).replace(matchPattern(), targetPattern());
        case ReplaceRule::Regex:return QString(alias).replace(QRegularExpression(matchPattern()), targetPattern());
    }
    Q_UNREACHABLE();
}

QJsonArray ReplaceRule::rulesToJson(const QVector<ReplaceRule>& rules)
{
    return Misc::arrayFromJsonValueVector(fplus::transform([](const ReplaceRule& rule)->QJsonValue{
            QJsonObject ruleJson;
            ruleJson.insert("matchPattern", rule.matchPattern());
            ruleJson.insert("targetPattern", rule.targetPattern());
            ruleJson.insert("strategy", rule.strategy());
            return ruleJson;
    }, rules));
}

QVector<ReplaceRule> ReplaceRule::jsonToRules(const QJsonArray& ruleJsonArray)
{
    return fplus::transform([](const QJsonValue& value)->ReplaceRule{
            auto obj = value.toObject();
            ReplaceRule rule;
            rule.setMatchPattern(obj.value("matchPattern").toString());
            rule.setTargetPattern(obj.value("targetPattern").toString());
            rule.setStrategy((ReplaceRule::MatchStrategy) obj.value("strategy").toInt());
            return rule;
        }, ruleJsonArray);
}
