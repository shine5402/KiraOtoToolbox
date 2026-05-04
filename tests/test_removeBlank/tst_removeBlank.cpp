#include <QtTest>

#include "removeBlank/RemoveBlankOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestRemoveBlank : public QObject
{
    Q_OBJECT
private slots:
    void testRemovesBlankEntries();
    void testKeepsNonBlankEntries();
    void testAllBlankYieldsEmpty();
    void testIgnoreRightFalse_keepsNegativeRight();
    void testIgnoreRightTrue_removesNegativeRight();
    void testCvVvEntriesNotBlank();
    void testEmptyInput();
};

void TestRemoveBlank::testRemovesBlankEntries()
{
    RemoveBlankOtoListModifyWorker worker;
    auto src = makeBlankEntryList();

    OtoEntryList result, secondSave;
    auto opts = makeOptions({{"ignoreRight", false}});
    worker.doWork(src, result, secondSave, opts);

    QVERIFY(result.isEmpty());
}

void TestRemoveBlank::testKeepsNonBlankEntries()
{
    RemoveBlankOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "", 0.0, 0.0, 0.0, 0.0, 0.0));          // blank
    src.append(makeEntry("b.wav", "alias", 0.0, 0.0, 0.0, 0.0, 0.0));     // has alias → not blank
    src.append(makeEntry("c.wav", "", 100.0, 0.0, 0.0, 0.0, 0.0));        // has left → not blank

    OtoEntryList result, secondSave;
    auto opts = makeOptions({{"ignoreRight", false}});
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), 2);
    QCOMPARE(result.at(0).fileName(), QString("b.wav"));
    QCOMPARE(result.at(1).fileName(), QString("c.wav"));
}

void TestRemoveBlank::testAllBlankYieldsEmpty()
{
    RemoveBlankOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("x.wav", "", 0.0, 0.0, 0.0, 0.0, 0.0));
    src.append(makeEntry("y.wav", "", 0.0, 0.0, 0.0, 0.0, 0.0));

    OtoEntryList result, secondSave;
    worker.doWork(src, result, secondSave, makeOptions({{"ignoreRight", false}}));

    QVERIFY(result.isEmpty());
}

void TestRemoveBlank::testIgnoreRightFalse_keepsNegativeRight()
{
    // ignoreRight=false: right must be exactly 0 to be blank
    // negative right != 0 → NOT blank
    RemoveBlankOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "", 0.0, 0.0, -100.0, 0.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({{"ignoreRight", false}});
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), 1);
}

void TestRemoveBlank::testIgnoreRightTrue_removesNegativeRight()
{
    // ignoreRight=true: right <= 0 counts as blank
    RemoveBlankOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "", 0.0, 0.0, -100.0, 0.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({{"ignoreRight", true}});
    worker.doWork(src, result, secondSave, opts);

    QVERIFY(result.isEmpty());
}

void TestRemoveBlank::testCvVvEntriesNotBlank()
{
    // CV-VV entries may have empty alias with non-zero params — must NOT be treated as blank
    RemoveBlankOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("_an.wav", "_an", 0.0, 70.0, 500.0, 70.0, 23.0));   // VV coda, has alias
    src.append(makeEntry("_ang.wav", "", 0.0, 75.0, 520.0, 75.0, 25.0));       // empty alias but non-zero params

    OtoEntryList result, secondSave;
    auto opts = makeOptions({{"ignoreRight", false}});
    worker.doWork(src, result, secondSave, opts);

    // Both kept: _an (has alias), _ang (empty alias but consonant != 0 → not blank)
    QCOMPARE(result.size(), 2);
    QCOMPARE(result.at(0).alias(), QString("_an"));
}

void TestRemoveBlank::testEmptyInput()
{
    RemoveBlankOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    worker.doWork({}, result, secondSave, makeOptions({{"ignoreRight", false}}));

    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestRemoveBlank)
#include "tst_removeBlank.moc"
