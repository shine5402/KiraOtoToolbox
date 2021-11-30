#ifndef COPYORREPLACEBYALIASRULE_H
#define COPYORREPLACEBYALIASRULE_H

#include <QString>
#include <QCoreApplication>

class CopyOrReplaceByAliasRule
{
    Q_DECLARE_TR_FUNCTIONS(CopyOrReplaceByAliasRule)
public:
    enum MatchStrategy{
        Exact = 0, Partial, Regex
    };

    CopyOrReplaceByAliasRule(QString matchPattern, QString targetPattern, MatchStrategy strategy);
    CopyOrReplaceByAliasRule();

    QString matchPattern() const;
    void setMatchPattern(const QString& value);

    QString targetPattern() const;
    void setTargetPattern(const QString& value);

    MatchStrategy strategy() const;
    void setStrategy(const MatchStrategy& value);
    static QString getStrategyString(MatchStrategy strategy);

    bool operator==(const CopyOrReplaceByAliasRule& other) const;

    bool match(const QString& alias) const;
    QString replace(const QString& alias) const;

private:
    QString matchPattern_;
    QString targetPattern_;
    MatchStrategy strategy_ = Exact;
};

Q_DECLARE_METATYPE(CopyOrReplaceByAliasRule)

#endif // COPYORREPLACEBYALIASRULE_H
