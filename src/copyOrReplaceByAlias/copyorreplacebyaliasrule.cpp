#include "copyorreplacebyaliasrule.h"
#include <QRegularExpression>

CopyOrReplaceByAliasRule::CopyOrReplaceByAliasRule(QString matchPattern, QString targetPattern,
                                                   CopyOrReplaceByAliasRule::MatchStrategy strategy):
    matchPattern_(std::move(matchPattern)), targetPattern_(std::move(targetPattern))
{
    this->strategy_ = strategy;
}

CopyOrReplaceByAliasRule::CopyOrReplaceByAliasRule()
{

}

QString CopyOrReplaceByAliasRule::matchPattern() const
{
    return matchPattern_;
}

void CopyOrReplaceByAliasRule::setMatchPattern(const QString& value)
{
    matchPattern_ = value;
}

QString CopyOrReplaceByAliasRule::targetPattern() const
{
    return targetPattern_;
}

void CopyOrReplaceByAliasRule::setTargetPattern(const QString& value)
{
    targetPattern_ = value;
}

CopyOrReplaceByAliasRule::MatchStrategy CopyOrReplaceByAliasRule::strategy() const
{
    return strategy_;
}

void CopyOrReplaceByAliasRule::setStrategy(const MatchStrategy& value)
{
    strategy_ = value;
}

QString CopyOrReplaceByAliasRule::getStrategyString(CopyOrReplaceByAliasRule::MatchStrategy strategy)
{
    switch (strategy) {
        case CopyOrReplaceByAliasRule::Exact:return tr("Exact");
        case CopyOrReplaceByAliasRule::Partial:return tr("Partial");
        case CopyOrReplaceByAliasRule::Regex:return tr("Regex");
    }
    return {};
}

bool CopyOrReplaceByAliasRule::operator==(const CopyOrReplaceByAliasRule& other) const
{
    return matchPattern() == other.matchPattern() && targetPattern() == other.targetPattern() && strategy() == other.strategy();
}

bool CopyOrReplaceByAliasRule::match(const QString& alias) const
{
    switch (strategy()){
        case CopyOrReplaceByAliasRule::Exact:return matchPattern().compare(alias) == 0;
        case CopyOrReplaceByAliasRule::Partial:return alias.contains(matchPattern());
        case CopyOrReplaceByAliasRule::Regex:return QRegularExpression{matchPattern()}.match(alias).hasMatch();
    }
    Q_UNREACHABLE();
}

QString CopyOrReplaceByAliasRule::replace(const QString& alias) const
{
    if (!match(alias))
        return alias;
    switch (strategy()){
        case CopyOrReplaceByAliasRule::Exact: [[fallthrough]];
        case CopyOrReplaceByAliasRule::Partial:return QString(alias).replace(matchPattern(), targetPattern());
        case CopyOrReplaceByAliasRule::Regex:return QString(alias).replace(QRegularExpression(matchPattern()), targetPattern());
    }
    Q_UNREACHABLE();
}
