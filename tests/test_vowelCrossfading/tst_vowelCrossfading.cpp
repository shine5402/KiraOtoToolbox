#include <QtTest>

#include "vowelCrossfading/VowelCrossfadingOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestVowelCrossfading : public QObject
{
    Q_OBJECT
private slots:
    void testCVOverride();
    void testCVCopy();
    void testLongRecordingMatch();
    void testRemoveNumberSuffixWhenMatching();
    void testVVOverlapIncrease();
    void testNoCrossfading_identity();
    void testEmptyInput();
};

void TestVowelCrossfading::testCVOverride()
{
    VowelCrossfadingOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("か.wav", "か", 100.0, 300.0, 1200.0, 300.0, 0.0));
    src.append(makeEntry("き.wav", "き", 100.0, 300.0, 1200.0, 300.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"doCVCrossfading", true},
        {"CVPreUtterance", 300.0},
        {"CVOverlap", 100.0},
        {"CVList", QStringList{"か"}},
        {"longRecordingPattern", QStringList{}},
        {"removeNumberSuffixWhenMatching", false},
        {"CVBehaviourOverride", true},
        {"CVBehaviourCopy", false},
        {"VVOverlapIncrease", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // "か" matched → PreUtterance and Overlap set
    auto ka = std::find_if(result.begin(), result.end(), [](const OtoEntry &e) {
        return e.alias() == "か";
    });
    QVERIFY(ka != result.end());
    QCOMPARE(ka->preUtterance(), 300.0);
    QCOMPARE(ka->overlap(), 100.0);

    // "き" not matched → unchanged
    auto ki = std::find_if(result.begin(), result.end(), [](const OtoEntry &e) {
        return e.alias() == "き";
    });
    QVERIFY(ki != result.end());
    QCOMPARE(ki->preUtterance(), 300.0); // original
    QCOMPARE(ki->overlap(), 0.0);        // original
}

void TestVowelCrossfading::testCVCopy()
{
    VowelCrossfadingOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("か.wav", "か", 100.0, 300.0, 1200.0, 300.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"doCVCrossfading", true},
        {"CVPreUtterance", 300.0},
        {"CVOverlap", 100.0},
        {"CVList", QStringList{"か"}},
        {"longRecordingPattern", QStringList{}},
        {"removeNumberSuffixWhenMatching", false},
        {"CVBehaviourOverride", false},
        {"CVBehaviourCopy", true},
        {"VVOverlapIncrease", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // Copy behaviour: original "か" gets modified + "* か" copy created
    QCOMPARE(result.size(), 2);
    auto starEntry = std::find_if(result.begin(), result.end(), [](const OtoEntry &e) {
        return e.alias() == "* か";
    });
    QVERIFY(starEntry != result.end());
    QCOMPARE(starEntry->overlap(), 100.0);
}

void TestVowelCrossfading::testLongRecordingMatch()
{
    VowelCrossfadingOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("か_long.wav", "か", 100.0, 300.0, 2000.0, 500.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"doCVCrossfading", true},
        {"CVPreUtterance", 500.0},
        {"CVOverlap", 150.0},
        {"CVList", QStringList{}},            // not in CVList directly
        {"longRecordingPattern", QStringList{"%a"}}, // but expands from VList via %a pattern
        {"removeNumberSuffixWhenMatching", false},
        {"CVBehaviourOverride", true},
        {"CVBehaviourCopy", false},
        {"VVOverlapIncrease", false},
        {"VList", QStringList{"か"}},          // source alias for longRecordingPattern expansion
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).preUtterance(), 500.0);
    QCOMPARE(result.at(0).overlap(), 150.0);
}

void TestVowelCrossfading::testRemoveNumberSuffixWhenMatching()
{
    VowelCrossfadingOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("か3.wav", "か3", 100.0, 300.0, 1200.0, 300.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"doCVCrossfading", true},
        {"CVPreUtterance", 300.0},
        {"CVOverlap", 100.0},
        {"CVList", QStringList{"か"}},
        {"longRecordingPattern", QStringList{}},
        {"removeNumberSuffixWhenMatching", true},
        {"CVBehaviourOverride", true},
        {"CVBehaviourCopy", false},
        {"VVOverlapIncrease", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // "か3" → digit removed → "か" matches CVList
    QCOMPARE(result.at(0).preUtterance(), 300.0);
    QCOMPARE(result.at(0).overlap(), 100.0);
}

void TestVowelCrossfading::testVVOverlapIncrease()
{
    VowelCrossfadingOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a か.wav", "a か", 100.0, 300.0, 1200.0, 300.0, 0.0));
    src.append(makeEntry("i か.wav", "i か", 100.0, 300.0, 1200.0, 240.0, 0.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"doCVCrossfading", false},
        {"VVOverlapIncrease", true},
        {"CVList", QStringList{"か"}},
        {"VList", QStringList{"a", "i"}},
        {"removeNumberSuffixWhenMatching", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // VV entries get overlap = preUtterance / 2
    QCOMPARE(result.at(0).overlap(), 150.0); // 300/2
    QCOMPARE(result.at(1).overlap(), 120.0); // 240/2
}

void TestVowelCrossfading::testNoCrossfading_identity()
{
    VowelCrossfadingOtoListModifyWorker worker;
    auto src = makeCvVoicebank();

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"doCVCrossfading", false},
        {"VVOverlapIncrease", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
    for (int i = 0; i < src.size(); ++i) {
        QVERIFY(result.at(i) == src.at(i));
    }
}

void TestVowelCrossfading::testEmptyInput()
{
    VowelCrossfadingOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"doCVCrossfading", false},
        {"VVOverlapIncrease", false},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestVowelCrossfading)
#include "tst_vowelCrossfading.moc"
