#include <QtTest>

#include "cvvcPartSplit/CVVCPartSplitOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestCvvcPartSplit : public QObject
{
    Q_OBJECT
private slots:
    void testPlainAlias_becomesCV();
    void testSpaceAlias_noPatternMatch_becomesVC();
    void testSpaceAlias_beginPatternMatch_becomesCV();
    void testCopyCVtoStartOto();
    void testIsSecondFileNameUsed();
    void testEmptyAlias_preserved();
    void testEmptyInput();
};

void TestCvvcPartSplit::testPlainAlias_becomesCV()
{
    CVVCPartSplitOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("か.wav", "か", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"isSeeBeginPatternAsCV", false},
        {"seeBeginPatternAsCVContent", QStringList{}},
        {"isSeeEndPatternAsCV", false},
        {"seeEndPatternAsCVContent", QStringList{}},
        {"copyCVtoStartOto", false},
        {"save/isSecondFileNameUsed", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // "か" has no space → automatically CV
    QCOMPARE(result.size(), 1);
    QCOMPARE(result.at(0).alias(), QString("か"));
}

void TestCvvcPartSplit::testSpaceAlias_noPatternMatch_becomesVC()
{
    CVVCPartSplitOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a k.wav", "a k", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("か.wav", "か", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"isSeeBeginPatternAsCV", false},
        {"seeBeginPatternAsCVContent", QStringList{}},
        {"isSeeEndPatternAsCV", false},
        {"seeEndPatternAsCVContent", QStringList{}},
        {"copyCVtoStartOto", false},
        {"save/isSecondFileNameUsed", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // "a k" has space, no pattern match → VC; "か" has no space → CV
    auto cv = std::find_if(result.begin(), result.end(), [](const OtoEntry &e) {
        return e.alias() == "か";
    });
    auto vc = std::find_if(result.begin(), result.end(), [](const OtoEntry &e) {
        return e.alias() == "a k";
    });
    QVERIFY(cv != result.end());
    QVERIFY(vc != result.end());
}

void TestCvvcPartSplit::testSpaceAlias_beginPatternMatch_becomesCV()
{
    CVVCPartSplitOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a かC4.wav", "a かC4", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("a k.wav", "a k", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"isSeeBeginPatternAsCV", true},
        {"seeBeginPatternAsCVContent", QStringList{"か"}},
        {"isSeeEndPatternAsCV", false},
        {"seeEndPatternAsCVContent", QStringList{}},
        {"copyCVtoStartOto", false},
        {"save/isSecondFileNameUsed", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // "a かC4" has space AND matches begin pattern "か" → CV
    // "a k" has space but doesn't match → VC
    auto cv = std::find_if(result.begin(), result.end(), [](const OtoEntry &e) {
        return e.alias() == "a かC4";
    });
    auto vc = std::find_if(result.begin(), result.end(), [](const OtoEntry &e) {
        return e.alias() == "a k";
    });
    QVERIFY(cv != result.end());
    QVERIFY(vc != result.end());
}

void TestCvvcPartSplit::testCopyCVtoStartOto()
{
    CVVCPartSplitOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("か.wav", "か", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"isSeeBeginPatternAsCV", false},
        {"seeBeginPatternAsCVContent", QStringList{}},
        {"isSeeEndPatternAsCV", false},
        {"seeEndPatternAsCVContent", QStringList{}},
        {"copyCVtoStartOto", true},
        {"save/isSecondFileNameUsed", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // Original "か" + start copy "- か"
    QCOMPARE(result.size(), 2);
    auto startEntry = std::find_if(result.begin(), result.end(), [](const OtoEntry &e) {
        return e.alias() == "- か";
    });
    QVERIFY(startEntry != result.end());
}

void TestCvvcPartSplit::testIsSecondFileNameUsed()
{
    CVVCPartSplitOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("か.wav", "か", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("a k.wav", "a k", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"isSeeBeginPatternAsCV", false},
        {"seeBeginPatternAsCVContent", QStringList{}},
        {"isSeeEndPatternAsCV", false},
        {"seeEndPatternAsCVContent", QStringList{}},
        {"copyCVtoStartOto", false},
        {"save/isSecondFileNameUsed", true},
    });
    worker.doWork(src, result, secondSave, opts);

    // VC goes to secondSaveOtoList, CV stays in result
    QCOMPARE(result.size(), 1);
    QCOMPARE(result.at(0).alias(), QString("か"));
    QCOMPARE(secondSave.size(), 1);
    QCOMPARE(secondSave.at(0).alias(), QString("a k"));
}

void TestCvvcPartSplit::testEmptyAlias_preserved()
{
    CVVCPartSplitOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("blank.wav", "", 0.0, 0.0, 0.0, 0.0, 0.0));
    src.append(makeEntry("か.wav", "か", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"isSeeBeginPatternAsCV", false},
        {"seeBeginPatternAsCVContent", QStringList{}},
        {"isSeeEndPatternAsCV", false},
        {"seeEndPatternAsCVContent", QStringList{}},
        {"copyCVtoStartOto", false},
        {"save/isSecondFileNameUsed", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // Empty alias entry preserved
    auto blank = std::find_if(result.begin(), result.end(), [](const OtoEntry &e) {
        return e.alias().isEmpty();
    });
    QVERIFY(blank != result.end());
}

void TestCvvcPartSplit::testEmptyInput()
{
    CVVCPartSplitOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"isSeeBeginPatternAsCV", false},
        {"seeBeginPatternAsCVContent", QStringList{}},
        {"isSeeEndPatternAsCV", false},
        {"seeEndPatternAsCVContent", QStringList{}},
        {"copyCVtoStartOto", false},
        {"save/isSecondFileNameUsed", false},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestCvvcPartSplit)
#include "tst_cvvcPartSplit.moc"
