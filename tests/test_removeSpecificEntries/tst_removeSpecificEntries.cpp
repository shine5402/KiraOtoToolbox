#include <QtTest>

#include "removeSpecificEntries/RemoveSpecificEntriesOtoListModifyWorker.h"
#include "removeSpecificEntries/RemoveSpecificEntriesOptionWidget.h"
#include "OtoTestUtils.h"

class TestRemoveSpecificEntries : public QObject
{
    Q_OBJECT
private slots:
    void testExactMatch();
    void testExactMatch_caseSensitive();
    void testPartialMatch();
    void testRegexMatch();
    void testNoMatch_keepsAll();
    void testEmptyPattern();
    void testEmptyInput();
};

void TestRemoveSpecificEntries::testExactMatch()
{
    RemoveSpecificEntriesOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "remove", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("b.wav", "keep", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"matchStrategy", (int)RemoveSpecificEntriesOptionWidget::Exact},
        {"pattern", "remove"},
        {"caseSensitive", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), 1);
    QCOMPARE(result.at(0).alias(), QString("keep"));
}

void TestRemoveSpecificEntries::testExactMatch_caseSensitive()
{
    RemoveSpecificEntriesOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "Remove", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("b.wav", "remove", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"matchStrategy", (int)RemoveSpecificEntriesOptionWidget::Exact},
        {"pattern", "remove"},
        {"caseSensitive", true},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), 1);
    QCOMPARE(result.at(0).alias(), QString("Remove"));
}

void TestRemoveSpecificEntries::testPartialMatch()
{
    RemoveSpecificEntriesOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "delete_me", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("b.wav", "me_keep", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("c.wav", "keep", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"matchStrategy", (int)RemoveSpecificEntriesOptionWidget::Partial},
        {"pattern", "delete"},
        {"caseSensitive", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), 2);
}

void TestRemoveSpecificEntries::testRegexMatch()
{
    RemoveSpecificEntriesOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test1", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("b.wav", "test2", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("c.wav", "keep", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"matchStrategy", (int)RemoveSpecificEntriesOptionWidget::Regex},
        {"pattern", R"(test\d)"},
        {"caseSensitive", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), 1);
    QCOMPARE(result.at(0).alias(), QString("keep"));
}

void TestRemoveSpecificEntries::testNoMatch_keepsAll()
{
    RemoveSpecificEntriesOtoListModifyWorker worker;
    auto src = makeCvVoicebank();

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"matchStrategy", (int)RemoveSpecificEntriesOptionWidget::Exact},
        {"pattern", "nonexistent"},
        {"caseSensitive", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
}

void TestRemoveSpecificEntries::testEmptyPattern()
{
    RemoveSpecificEntriesOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "hello", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"matchStrategy", (int)RemoveSpecificEntriesOptionWidget::Exact},
        {"pattern", ""},
        {"caseSensitive", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // Empty pattern won't match "hello" in exact mode
    QCOMPARE(result.size(), 1);
}

void TestRemoveSpecificEntries::testEmptyInput()
{
    RemoveSpecificEntriesOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"matchStrategy", (int)RemoveSpecificEntriesOptionWidget::Exact},
        {"pattern", "x"},
        {"caseSensitive", false},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestRemoveSpecificEntries)
#include "tst_removeSpecificEntries.moc"
