#include <QtTest>
#include <QTemporaryDir>

#include "replaceFileName/ReplaceFileNameOtoListModifyWorker.h"
#include "utils/widgets/ReplaceRule.h"
#include "OtoTestUtils.h"

class TestReplaceFileName : public QObject
{
    Q_OBJECT
private slots:
    void testReplaceExact();
    void testReplacePartial();
    void testReplaceRegex();
    void testNoMatch_unchanged();
    void testEmptyRules_identity();
    void testOnlyMatchingEntryChanged();
    void testEmptyInput();
};

void TestReplaceFileName::testReplaceExact()
{
    ReplaceFileNameOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("old.wav", "test", 100.0, 300.0, 1000.0, 150.0, 50.0));

    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule("old", "new", ReplaceRule::Exact));

    OtoEntryList result, secondSave;
    // Need a dummy oto file path for load/fileName
    auto opts = makeOptions({
        {"load/fileName", "/tmp/dummy.ini"},
        {"rules", QVariant::fromValue(rules)},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).fileName(), QString("new.wav"));
}

void TestReplaceFileName::testReplacePartial()
{
    ReplaceFileNameOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("prefix_suffix.wav", "test", 100.0, 300.0, 1000.0, 150.0, 50.0));

    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule("prefix", "new", ReplaceRule::Partial));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"load/fileName", "/tmp/dummy.ini"},
        {"rules", QVariant::fromValue(rules)},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).fileName(), QString("new_suffix.wav"));
}

void TestReplaceFileName::testReplaceRegex()
{
    ReplaceFileNameOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("file_001.wav", "test", 100.0, 300.0, 1000.0, 150.0, 50.0));

    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule(R"(\d+)", "XXX", ReplaceRule::Regex));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"load/fileName", "/tmp/dummy.ini"},
        {"rules", QVariant::fromValue(rules)},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).fileName(), QString("file_XXX.wav"));
}

void TestReplaceFileName::testNoMatch_unchanged()
{
    ReplaceFileNameOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("keep.wav", "test", 100.0, 300.0, 1000.0, 150.0, 50.0));

    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule("nonexistent", "x", ReplaceRule::Exact));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"load/fileName", "/tmp/dummy.ini"},
        {"rules", QVariant::fromValue(rules)},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).fileName(), QString("keep.wav"));
}

void TestReplaceFileName::testEmptyRules_identity()
{
    ReplaceFileNameOtoListModifyWorker worker;
    auto src = makeCvVoicebank();

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"load/fileName", "/tmp/dummy.ini"},
        {"rules", QVariant::fromValue(QVector<ReplaceRule>{})},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
    for (int i = 0; i < src.size(); ++i)
        QCOMPARE(result.at(i).fileName(), src.at(i).fileName());
}

void TestReplaceFileName::testOnlyMatchingEntryChanged()
{
    ReplaceFileNameOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "x", 100.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("b.wav", "y", 100.0, 300.0, 1000.0, 150.0, 50.0));

    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule("a", "changed", ReplaceRule::Exact));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"load/fileName", "/tmp/dummy.ini"},
        {"rules", QVariant::fromValue(rules)},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).fileName(), QString("changed.wav"));
    QCOMPARE(result.at(1).fileName(), QString("b.wav")); // unchanged
}

void TestReplaceFileName::testEmptyInput()
{
    ReplaceFileNameOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    QVector<ReplaceRule> rules;
    rules.append(ReplaceRule("a", "b", ReplaceRule::Exact));
    auto opts = makeOptions({
        {"load/fileName", "/tmp/dummy.ini"},
        {"rules", QVariant::fromValue(rules)},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestReplaceFileName)
#include "tst_replaceFileName.moc"
