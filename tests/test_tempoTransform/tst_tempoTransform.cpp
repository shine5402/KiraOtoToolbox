#include <QtTest>

#include "tempoTransform/TempoTransformOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestTempoTransform : public QObject
{
    Q_OBJECT
private slots:
    void testIdentityTempo();
    void testDoubleSpeed();
    void testHalfSpeed();
    void testOffsetOnly();
    void testSingleEntryPerFile();
    void testNegativeRight_unchanged();
    void testEmptyInput();
    void testMultipleEntriesPerFile();
};

void TestTempoTransform::testIdentityTempo()
{
    TempoTransformOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "x", 100.0, 300.0, 500.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"offset", 0.0},
        {"fromTempo", 120.0},
        {"toTempo", 120.0},
    });
    worker.doWork(src, result, secondSave, opts);

    // Same tempo = identity (ratio = 1)
    // Single entry per file → diff = 0, offset = 0 → no change
    QCOMPARE(result.at(0).left(), 100.0);
    QCOMPARE(result.at(0).right(), 500.0);
}

void TestTempoTransform::testDoubleSpeed()
{
    TempoTransformOtoListModifyWorker worker;
    // Two entries with same filename → they form a pair
    OtoEntryList src;
    src.append(makeEntry("same.wav", "a", 100.0, 300.0, 800.0, 200.0, 50.0));
    src.append(makeEntry("same.wav", "b", 200.0, 350.0, 900.0, 300.0, 60.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"offset", 0.0},
        {"fromTempo", 120.0},
        {"toTempo", 60.0}, // half speed → ratio = 120/60 = 2.0
    });
    worker.doWork(src, result, secondSave, opts);

    // Distance = absolutePre(1) - absolutePre(0) = (200+300) - (100+200) = 500-300 = 200
    // newDistance = 200 * 2 = 400, diff = 400-200 = 200
    // Entry 0: left = 100+0+0 = 100, right = 800-(0+0) = 800
    // Entry 1: left = 200+200+0 = 400, right = 900-(200+0) = 700
    QCOMPARE(result.at(0).left(), 100.0);
    QCOMPARE(result.at(1).left(), 400.0);
    QCOMPARE(result.at(1).right(), 700.0);
}

void TestTempoTransform::testHalfSpeed()
{
    TempoTransformOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("same.wav", "a", 100.0, 300.0, 800.0, 200.0, 50.0));
    src.append(makeEntry("same.wav", "b", 300.0, 350.0, 900.0, 300.0, 60.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"offset", 0.0},
        {"fromTempo", 60.0},
        {"toTempo", 120.0}, // double speed → ratio = 60/120 = 0.5
    });
    worker.doWork(src, result, secondSave, opts);

    // Distance = (300+300) - (100+200) = 600-300 = 300
    // newDistance = 300 * 0.5 = 150, diff = 150-300 = -150
    // Entry 0: left = 100+0+0 = 100
    // Entry 1: left = 300+(-150)+0 = 150, right = 900-(-150) = 1050
    QCOMPARE(result.at(0).left(), 100.0);
    QCOMPARE(result.at(1).left(), 150.0);
    QCOMPARE(result.at(1).right(), 1050.0);
}

void TestTempoTransform::testOffsetOnly()
{
    TempoTransformOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "x", 100.0, 300.0, 800.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"offset", 50.0},
        {"fromTempo", 120.0},
        {"toTempo", 120.0},
    });
    worker.doWork(src, result, secondSave, opts);

    // Single entry: diff=0, only offset applied
    QCOMPARE(result.at(0).left(), 150.0);  // 100 + 50
    QCOMPARE(result.at(0).right(), 750.0); // 800 - 50
}

void TestTempoTransform::testSingleEntryPerFile()
{
    TempoTransformOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "x", 100.0, 300.0, 500.0, 200.0, 50.0));
    src.append(makeEntry("b.wav", "y", 200.0, 350.0, 600.0, 300.0, 60.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"offset", 0.0},
        {"fromTempo", 120.0},
        {"toTempo", 60.0},
    });
    worker.doWork(src, result, secondSave, opts);

    // Each in its own group → no pair → diff stays 0
    QCOMPARE(result.size(), 2);
}

void TestTempoTransform::testNegativeRight_unchanged()
{
    TempoTransformOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("same.wav", "a", 100.0, 300.0, -1.0, 200.0, 50.0));
    src.append(makeEntry("same.wav", "b", 200.0, 350.0, -1.0, 300.0, 60.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"offset", 0.0},
        {"fromTempo", 120.0},
        {"toTempo", 60.0},
    });
    worker.doWork(src, result, secondSave, opts);

    // right <= 0 → not adjusted
    QCOMPARE(result.at(0).right(), -1.0);
    QCOMPARE(result.at(1).right(), -1.0);
}

void TestTempoTransform::testEmptyInput()
{
    TempoTransformOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"offset", 0.0},
        {"fromTempo", 120.0},
        {"toTempo", 120.0},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

void TestTempoTransform::testMultipleEntriesPerFile()
{
    // Three entries in same file spaced 500ms apart → per-group group_by + adjacent + zip
    // From 120 BPM to 60 BPM: ratio = 120/60 = 2.0 (double speed)
    TempoTransformOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("test.wav", "a", 0.0, 100.0, -100.0, 0.0, 0.0));
    src.append(makeEntry("test.wav", "b", 500.0, 100.0, -100.0, 0.0, 0.0));
    src.append(makeEntry("test.wav", "c", 1000.0, 100.0, -100.0, 0.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"offset", 0.0},
        {"fromTempo", 120.0},
        {"toTempo", 60.0},
    });
    worker.doWork(src, result, secondSave, opts);

    // absolutePre = left + preUtterance = left + 0 = left
    // distances: (500-0)=500, (1000-500)=500
    // new distances: 500*2=1000, 500*2=1000
    // diff: 1000-500=500, 1000-500=500; prepend 0 → [0, 500, 500]
    // a: left = 0 + 0 + 0 = 0
    // b: left = 500 + 500 + 0 = 1000
    // c: left = 1000 + 500 + 0 = 1500
    QCOMPARE(result.size(), 3);
    QCOMPARE(result.at(0).left(), 0.0);
    QCOMPARE(result.at(1).left(), 1000.0);
    QCOMPARE(result.at(2).left(), 1500.0);
}

QTEST_MAIN(TestTempoTransform)
#include "tst_tempoTransform.moc"
