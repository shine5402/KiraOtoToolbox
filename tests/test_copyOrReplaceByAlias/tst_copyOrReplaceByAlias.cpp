#include <QtTest>

#include "copyOrReplaceByAlias/CopyOrReplaceByAliasOtoListModifyWorker.h"
#include "utils/widgets/ReplaceRule.h"
#include "OtoTestUtils.h"

class TestCopyOrReplaceByAlias : public QObject
{
    Q_OBJECT
private slots:
    void testExactMatch_replace();
    void testExactMatch_copy();
    void testPartialMatch();
    void testRegexMatch();
    void testMatchFirstStrategy();
    void testMatchAllSequential();
    void testNoMatch_identity();
    void testEmptyRules_identity();
    void testEmptyInput();
};

void TestCopyOrReplaceByAlias::testExactMatch_replace()
{
    CopyOrReplaceByAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "hello", 0.0, 300.0, 1000.0, 150.0, 50.0));

    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule("hello", "world", ReplaceRule::Exact));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"rules", QVariant::fromValue(rules)},
        {"behaviorCopy", false},
        {"behaviorReplace", true},
        {"opStrategy", 0},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), 1);
    QCOMPARE(result.at(0).alias(), QString("world"));
}

void TestCopyOrReplaceByAlias::testExactMatch_copy()
{
    CopyOrReplaceByAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "hello", 0.0, 300.0, 1000.0, 150.0, 50.0));

    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule("hello", "world", ReplaceRule::Exact));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"rules", QVariant::fromValue(rules)},
        {"behaviorCopy", true},
        {"behaviorReplace", false},
        {"opStrategy", 0},
    });
    worker.doWork(src, result, secondSave, opts);

    // Copy: original "hello" order-preserved, then new "world" inserted after
    QCOMPARE(result.size(), 2);
    QCOMPARE(result.at(0).alias(), QString("hello"));
    QCOMPARE(result.at(1).alias(), QString("world"));
}

void TestCopyOrReplaceByAlias::testPartialMatch()
{
    CopyOrReplaceByAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "hello_world", 0.0, 300.0, 1000.0, 150.0, 50.0));

    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule("hello", "hi", ReplaceRule::Partial));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"rules", QVariant::fromValue(rules)},
        {"behaviorCopy", false},
        {"behaviorReplace", true},
        {"opStrategy", 0},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("hi_world"));
}

void TestCopyOrReplaceByAlias::testRegexMatch()
{
    CopyOrReplaceByAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test123", 0.0, 300.0, 1000.0, 150.0, 50.0));

    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule(R"(\d+)", "num", ReplaceRule::Regex));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"rules", QVariant::fromValue(rules)},
        {"behaviorCopy", false},
        {"behaviorReplace", true},
        {"opStrategy", 0},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("testnum"));
}

void TestCopyOrReplaceByAlias::testMatchFirstStrategy()
{
    CopyOrReplaceByAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "ab", 0.0, 300.0, 1000.0, 150.0, 50.0));

    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule("a", "1", ReplaceRule::Partial));
    rules.append(ReplaceRule("b", "2", ReplaceRule::Partial));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"rules", QVariant::fromValue(rules)},
        {"behaviorCopy", false},
        {"behaviorReplace", true},
        {"opStrategy", 0}, // Match first then stop
    });
    worker.doWork(src, result, secondSave, opts);

    // First rule matches "ab" (contains "a"), stops there
    QCOMPARE(result.at(0).alias(), QString("1b"));
}

void TestCopyOrReplaceByAlias::testMatchAllSequential()
{
    CopyOrReplaceByAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "ab", 0.0, 300.0, 1000.0, 150.0, 50.0));

    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule("a", "1", ReplaceRule::Partial));
    rules.append(ReplaceRule("b", "2", ReplaceRule::Partial));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"rules", QVariant::fromValue(rules)},
        {"behaviorCopy", false},
        {"behaviorReplace", true},
        {"opStrategy", 1}, // Match all sequentially
    });
    worker.doWork(src, result, secondSave, opts);

    // Both rules applied sequentially: "ab" → "1b" → "12"
    QCOMPARE(result.at(0).alias(), QString("12"));
}

void TestCopyOrReplaceByAlias::testNoMatch_identity()
{
    CopyOrReplaceByAliasOtoListModifyWorker worker;
    auto src = makeCvVoicebank();

    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule("nonexistent", "x", ReplaceRule::Exact));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"rules", QVariant::fromValue(rules)},
        {"behaviorCopy", false},
        {"behaviorReplace", true},
        {"opStrategy", 0},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
    for (int i = 0; i < src.size(); ++i) {
        QCOMPARE(result.at(i).alias(), src.at(i).alias());
    }
}

void TestCopyOrReplaceByAlias::testEmptyRules_identity()
{
    CopyOrReplaceByAliasOtoListModifyWorker worker;
    auto src = makeCvVoicebank();

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"rules", QVariant::fromValue(QVector<ReplaceRule>{})},
        {"behaviorCopy", false},
        {"behaviorReplace", true},
        {"opStrategy", 0},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
}

void TestCopyOrReplaceByAlias::testEmptyInput()
{
    CopyOrReplaceByAliasOtoListModifyWorker worker;
    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule("a", "b", ReplaceRule::Exact));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"rules", QVariant::fromValue(rules)},
        {"behaviorCopy", false},
        {"behaviorReplace", true},
        {"opStrategy", 0},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestCopyOrReplaceByAlias)
#include "tst_copyOrReplaceByAlias.moc"
