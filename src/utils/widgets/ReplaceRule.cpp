#include "ReplaceRule.h"

#include <QRegularExpression>

#include "qjsonarray.h"
#include "utils/misc/Misc.h"

ReplaceRule::ReplaceRule(QString matchPattern, QString targetPattern, ReplaceRule::MatchStrategy strategy)
    : matchPattern_(std::move(matchPattern)), targetPattern_(std::move(targetPattern))
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

void ReplaceRule::setMatchPattern(const QString &value)
{
    matchPattern_ = value;
}

QString ReplaceRule::targetPattern() const
{
    return targetPattern_;
}

void ReplaceRule::setTargetPattern(const QString &value)
{
    targetPattern_ = value;
}

ReplaceRule::MatchStrategy ReplaceRule::strategy() const
{
    return strategy_;
}

void ReplaceRule::setStrategy(const MatchStrategy &value)
{
    strategy_ = value;
}

QString ReplaceRule::getStrategyString(ReplaceRule::MatchStrategy strategy)
{
    switch (strategy) {
    case ReplaceRule::Exact:
        return tr("Exact");
    case ReplaceRule::Partial:
        return tr("Partial");
    case ReplaceRule::Regex:
        return tr("Regex");
    }
    return {};
}

bool ReplaceRule::operator==(const ReplaceRule &other) const
{
    return matchPattern() == other.matchPattern() && targetPattern() == other.targetPattern() &&
           strategy() == other.strategy();
}

bool ReplaceRule::match(const QString &alias) const
{
    switch (strategy()) {
    case ReplaceRule::Exact:
        return matchPattern().compare(alias) == 0;
    case ReplaceRule::Partial:
        return alias.contains(matchPattern());
    case ReplaceRule::Regex:
        return QRegularExpression{matchPattern()}.match(alias).hasMatch();
    }
    Q_UNREACHABLE();
}

QString ReplaceRule::replace(const QString &alias) const
{
    if (!match(alias))
        return alias;
    switch (strategy()) {
    case ReplaceRule::Exact:
        [[fallthrough]];
    case ReplaceRule::Partial:
        return QString(alias).replace(matchPattern(), targetPattern());
    case ReplaceRule::Regex:
        return QString(alias).replace(QRegularExpression(matchPattern()), targetPattern());
    }
    Q_UNREACHABLE();
}

QJsonArray ReplaceRule::rulesToJson(const QVector<ReplaceRule> &rules)
{
    QVector<QJsonValue> jsonValues;
    jsonValues.reserve(rules.size());
    for (const auto &rule : rules) {
        QJsonObject ruleJson;
        ruleJson.insert("matchPattern", rule.matchPattern());
        ruleJson.insert("targetPattern", rule.targetPattern());
        ruleJson.insert("strategy", rule.strategy());
        jsonValues.append(ruleJson);
    }
    return Misc::arrayFromJsonValueVector(jsonValues);
}

QVector<ReplaceRule> ReplaceRule::jsonToRules(const QJsonArray &ruleJsonArray)
{
    QVector<ReplaceRule> result;
    result.reserve(ruleJsonArray.size());
    for (const auto &value : ruleJsonArray) {
        auto obj = value.toObject();
        ReplaceRule rule;
        rule.setMatchPattern(obj.value("matchPattern").toString());
        rule.setTargetPattern(obj.value("targetPattern").toString());
        rule.setStrategy((ReplaceRule::MatchStrategy)obj.value("strategy").toInt());
        result.append(rule);
    }
    return result;
}
