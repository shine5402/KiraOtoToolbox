#include <QtTest>

#include "trimAroundSpecificValue/TrimAroundSpecificValueOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestTrimAroundSpecificValue : public QObject
{
    Q_OBJECT
private slots:
    void testTrimWithinRange();
    void testTrimOutsideRange_unchanged();
    void testTrimAtBoundary();
    void testMissingField_throws();
    void testEmptyInput();
};

void TestTrimAroundSpecificValue::testTrimWithinRange()
{
    TrimAroundSpecificValueOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 98.0, 300.0, 1000.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"field", (int)OtoEntry::LEFT},
        {"targetValue", 100.0},
        {"roundingRange", 5.0},
    });
    worker.doWork(src, result, secondSave, opts);

    // 98 is within 100±5 → snapped to 100
    QCOMPARE(result.at(0).left(), 100.0);
}

void TestTrimAroundSpecificValue::testTrimOutsideRange_unchanged()
{
    TrimAroundSpecificValueOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 50.0, 300.0, 1000.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"field", (int)OtoEntry::LEFT},
        {"targetValue", 100.0},
        {"roundingRange", 5.0},
    });
    worker.doWork(src, result, secondSave, opts);

    // 50 is outside 100±5 → unchanged
    QCOMPARE(result.at(0).left(), 50.0);
}

void TestTrimAroundSpecificValue::testTrimAtBoundary()
{
    TrimAroundSpecificValueOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 300.0, 95.0, 1000.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"field", (int)OtoEntry::CONSONANT},
        {"targetValue", 100.0},
        {"roundingRange", 5.0},
    });
    worker.doWork(src, result, secondSave, opts);

    // 95 is at boundary (100-5=95, exclusive on left side per code: > not >=)
    // Actually: fieldValue > targetValue - roundingEdge → 95 > 95 is false → not trimmed
    QCOMPARE(result.at(0).consonant(), 95.0);
}

void TestTrimAroundSpecificValue::testMissingField_throws()
{
    TrimAroundSpecificValueOtoListModifyWorker worker;
    OtoEntryList src, result, secondSave;
    OptionContainer opts; // no "field" key

    QVERIFY_THROWS_EXCEPTION(ToolException, worker.doWork(src, result, secondSave, opts));
}

void TestTrimAroundSpecificValue::testEmptyInput()
{
    TrimAroundSpecificValueOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"field", (int)OtoEntry::LEFT},
        {"targetValue", 100.0},
        {"roundingRange", 5.0},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestTrimAroundSpecificValue)
#include "tst_trimAroundSpecificValue.moc"
