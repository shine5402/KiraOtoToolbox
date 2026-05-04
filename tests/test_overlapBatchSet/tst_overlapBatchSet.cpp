#include <QtTest>

#include "overlapBatchSet/OverlapBatchSetOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestOverlapBatchSet : public QObject
{
    Q_OBJECT
private slots:
    void testSetOverlapByStartPattern();
    void testStartPatternNotMatched_makeOneThird();
    void testMakeOneThird();
    void testOneSecondWhenTooSmall();
    void testAlreadyMatched_skipOneThird();
    void testEmptyInput();
};

void TestOverlapBatchSet::testSetOverlapByStartPattern()
{
    OverlapBatchSetOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "か", 0.0, 300.0, 1000.0, 300.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"ifSetOverlapStartWith", true},
        {"startWithPatternList", QStringList{"か"}},
        {"ifMatchStartOto", false},
        {"overlapStartWith", 100.0},
        {"makeOneThird", false},
        {"oneSecondWhenTooSmall", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).overlap(), 100.0);
}

void TestOverlapBatchSet::testStartPatternNotMatched_makeOneThird()
{
    OverlapBatchSetOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "あ", 0.0, 300.0, 1000.0, 300.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"ifSetOverlapStartWith", true},
        {"startWithPatternList", QStringList{"か"}},
        {"ifMatchStartOto", false},
        {"overlapStartWith", 100.0},
        {"makeOneThird", true},
        {"oneSecondWhenTooSmall", false},
        {"oneSecondWhenTooSmallValue", 30.0},
    });
    worker.doWork(src, result, secondSave, opts);

    // Not matched by start pattern → falls back to one-third
    QCOMPARE(result.at(0).overlap(), 300.0 / 3.0);
}

void TestOverlapBatchSet::testMakeOneThird()
{
    OverlapBatchSetOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "き", 0.0, 300.0, 1000.0, 300.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"ifSetOverlapStartWith", false},
        {"makeOneThird", true},
        {"oneSecondWhenTooSmall", false},
        {"oneSecondWhenTooSmallValue", 30.0},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).overlap(), 100.0); // preUtterance/3 = 300/3
}

void TestOverlapBatchSet::testOneSecondWhenTooSmall()
{
    OverlapBatchSetOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 0.0, 100.0, 500.0, 60.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"ifSetOverlapStartWith", false},
        {"makeOneThird", true},
        {"oneSecondWhenTooSmall", true},
        {"oneSecondWhenTooSmallValue", 50.0},
    });
    worker.doWork(src, result, secondSave, opts);

    // preUtterance/3 = 20, which is < 50 → use preUtterance/2 = 30
    QCOMPARE(result.at(0).overlap(), 30.0);
}

void TestOverlapBatchSet::testAlreadyMatched_skipOneThird()
{
    OverlapBatchSetOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "か", 0.0, 300.0, 1000.0, 300.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"ifSetOverlapStartWith", true},
        {"startWithPatternList", QStringList{"か"}},
        {"ifMatchStartOto", false},
        {"overlapStartWith", 50.0},
        {"makeOneThird", true},
        {"oneSecondWhenTooSmall", false},
        {"oneSecondWhenTooSmallValue", 30.0},
    });
    worker.doWork(src, result, secondSave, opts);

    // Matched by start pattern → overlap = 50, NOT one-third
    QCOMPARE(result.at(0).overlap(), 50.0);
}

void TestOverlapBatchSet::testEmptyInput()
{
    OverlapBatchSetOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"ifSetOverlapStartWith", false},
        {"makeOneThird", true},
        {"oneSecondWhenTooSmall", false},
        {"oneSecondWhenTooSmallValue", 30.0},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestOverlapBatchSet)
#include "tst_overlapBatchSet.moc"
