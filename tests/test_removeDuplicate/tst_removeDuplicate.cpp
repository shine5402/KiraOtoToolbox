#include <QtTest>

#include "removeDuplicate/RemoveDuplicateOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestRemoveDuplicate : public QObject
{
    Q_OBJECT
private slots:
    void testNoLimit_keepsAll();
    void testMaxCount_removesExcess();
    void testMaxCountZero_keepsAll();
    void testSecondSaveOtoList_populated();
    void testUniqueAliases_allKept();
    void testConsiderNegativeSuffix();
    void testEmptyInput();
};

void TestRemoveDuplicate::testNoLimit_keepsAll()
{
    RemoveDuplicateOtoListModifyWorker worker;
    auto src = makeDuplicateAliasList();

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"maxDuplicateCount", 0},
        {"considerNegativeSuffix", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // maxDuplicateCount=0 means no limit, all kept
    QCOMPARE(result.size(), src.size());
}

void TestRemoveDuplicate::testMaxCount_removesExcess()
{
    RemoveDuplicateOtoListModifyWorker worker;
    auto src = makeDuplicateAliasList(); // 3x "test", 2x "other"

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"maxDuplicateCount", 1},
        {"considerNegativeSuffix", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // Only 1 of each alias kept → 2 entries
    QCOMPARE(result.size(), 2);
    // "test" once, "other" once
    int testCount = 0, otherCount = 0;
    for (const auto &e : result) {
        if (e.alias() == "test") testCount++;
        if (e.alias() == "other") otherCount++;
    }
    QCOMPARE(testCount, 1);
    QCOMPARE(otherCount, 1);
}

void TestRemoveDuplicate::testMaxCountZero_keepsAll()
{
    RemoveDuplicateOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "dup", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("b.wav", "dup", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"maxDuplicateCount", 0},
        {"considerNegativeSuffix", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), 2);
}

void TestRemoveDuplicate::testSecondSaveOtoList_populated()
{
    RemoveDuplicateOtoListModifyWorker worker;
    auto src = makeDuplicateAliasList();

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"maxDuplicateCount", 1},
        {"considerNegativeSuffix", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // Excess entries go to secondSaveOtoList
    QVERIFY(!secondSave.isEmpty());
}

void TestRemoveDuplicate::testUniqueAliases_allKept()
{
    RemoveDuplicateOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "one", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("b.wav", "two", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"maxDuplicateCount", 1},
        {"considerNegativeSuffix", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), 2);
    QVERIFY(secondSave.isEmpty());
}

void TestRemoveDuplicate::testConsiderNegativeSuffix()
{
    RemoveDuplicateOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "alias", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("b.wav", "alias-1", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"maxDuplicateCount", 1},
        {"considerNegativeSuffix", true},
    });
    worker.doWork(src, result, secondSave, opts);

    // "-1" is a negative suffix; with considerNegativeSuffix, both become "alias" → duplicate
    QCOMPARE(result.size(), 1);
}

void TestRemoveDuplicate::testEmptyInput()
{
    RemoveDuplicateOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"maxDuplicateCount", 1},
        {"considerNegativeSuffix", false},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestRemoveDuplicate)
#include "tst_removeDuplicate.moc"
