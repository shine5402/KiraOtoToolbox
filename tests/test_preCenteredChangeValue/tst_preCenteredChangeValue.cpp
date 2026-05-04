#include <QtTest>

#include "preCenteredChangeValue/PreCenteredChangeValueOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestPreCenteredChangeValue : public QObject
{
    Q_OBJECT
private slots:
    void testChangeConstField();
    void testChangePreutterance();
    void testChangePreutterance_leftClamping();
    void testChangeOverlap();
    void testChangeRight();
    void testChangeAllFields();
    void testNoChangeSelected();
    void testEmptyInput();
};

void TestPreCenteredChangeValue::testChangeConstField()
{
    PreCenteredChangeValueOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 100.0, 300.0, 1000.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"changeConstField", true},
        {"constField", 500.0},
        {"changePreutterance", false},
        {"changeOverlap", false},
        {"changeRight", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).consonant(), 500.0);
    QCOMPARE(result.at(0).left(), 100.0); // unchanged
    QCOMPARE(result.at(0).preUtterance(), 200.0); // unchanged
}

void TestPreCenteredChangeValue::testChangePreutterance()
{
    PreCenteredChangeValueOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 100.0, 300.0, 1000.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"changeConstField", false},
        {"changePreutterance", true},
        {"preutterance", 250.0},
        {"changeOverlap", false},
        {"changeRight", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // preDiff = 200 - 250 = -50, newLeft = 100 + (-50) = 50, still >= 0, so preUtterance = 250
    QCOMPARE(result.at(0).preUtterance(), 250.0);
    QCOMPARE(result.at(0).left(), 50.0);
    // consonant adjusted: 300 - (-50) = 350
    QCOMPARE(result.at(0).consonant(), 350.0);
}

void TestPreCenteredChangeValue::testChangePreutterance_leftClamping()
{
    PreCenteredChangeValueOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 50.0, 200.0, 800.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"changeConstField", false},
        {"changePreutterance", true},
        {"preutterance", 300.0},
        {"changeOverlap", false},
        {"changeRight", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // preDiff = 150 - 300 = -150, newLeft = 50 + (-150) = -100, which is < 0
    // Should clamp: left stays 50, preUtterance stays 150
    QCOMPARE(result.at(0).preUtterance(), 150.0);
    QCOMPARE(result.at(0).left(), 50.0);
}

void TestPreCenteredChangeValue::testChangeOverlap()
{
    PreCenteredChangeValueOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 100.0, 300.0, 1000.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"changeConstField", false},
        {"changePreutterance", false},
        {"changeOverlap", true},
        {"overlap", 80.0},
        {"changeRight", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).overlap(), 80.0);
}

void TestPreCenteredChangeValue::testChangeRight()
{
    PreCenteredChangeValueOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 100.0, 300.0, 1000.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"changeConstField", false},
        {"changePreutterance", false},
        {"changeOverlap", false},
        {"changeRight", true},
        {"right", 1500.0},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).right(), 1500.0);
}

void TestPreCenteredChangeValue::testChangeAllFields()
{
    PreCenteredChangeValueOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 100.0, 300.0, 1000.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"changeConstField", true},
        {"constField", 500.0},
        {"changePreutterance", true},
        {"preutterance", 250.0},
        {"changeOverlap", true},
        {"overlap", 80.0},
        {"changeRight", true},
        {"right", 1500.0},
    });
    worker.doWork(src, result, secondSave, opts);

    // preUtterance changed (with left adjustment), constField overrides, overlap set, right set
    QCOMPARE(result.at(0).preUtterance(), 250.0);
    QCOMPARE(result.at(0).consonant(), 500.0); // overridden by changeConstField
    QCOMPARE(result.at(0).overlap(), 80.0);
    QCOMPARE(result.at(0).right(), 1500.0);
}

void TestPreCenteredChangeValue::testNoChangeSelected()
{
    PreCenteredChangeValueOtoListModifyWorker worker;
    auto src = makeCvVoicebank();

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"changeConstField", false},
        {"changePreutterance", false},
        {"changeOverlap", false},
        {"changeRight", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
    for (int i = 0; i < src.size(); ++i) {
        QVERIFY(result.at(i) == src.at(i));
    }
}

void TestPreCenteredChangeValue::testEmptyInput()
{
    PreCenteredChangeValueOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"changeConstField", true},
        {"constField", 500.0},
        {"changePreutterance", false},
        {"changeOverlap", false},
        {"changeRight", false},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestPreCenteredChangeValue)
#include "tst_preCenteredChangeValue.moc"
