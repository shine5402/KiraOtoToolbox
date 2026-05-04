#include <QtTest>

#include "mergeOto/MergeOtoOtoListModifyWorker.h"
#include "mergeOto/MergeOtoOptionWidget.h"
#include "OtoTestUtils.h"

class TestMergeOto : public QObject
{
    Q_OBJECT
private slots:
    void testReplaceStrategy();
    void testSkipStrategy();
    void testKeepAllStrategy();
    void testEmptyOtherList();
    void testNotLoadedThrows();
    void testEmptyInput();
};

void TestMergeOto::testReplaceStrategy()
{
    MergeOtoOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "shared", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("b.wav", "only_src", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList other;
    other.append(makeEntry("x.wav", "shared", 0.0, 500.0, 2000.0, 200.0, 80.0));  // replaces "shared"
    other.append(makeEntry("y.wav", "only_other", 0.0, 300.0, 1000.0, 150.0, 50.0)); // added

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"otherOtoLoaded", true},
        {"otherOtoList", QVariant::fromValue(other)},
        {"mergeStrategy", (int)MergeOtoOptionWidget::Replace},
    });
    worker.doWork(src, result, secondSave, opts);

    // "shared" replaced, "only_other" appended → 3 entries
    QCOMPARE(result.size(), 3);
    // Find the replaced "shared" entry
    auto sharedEntry = std::find_if(result.begin(), result.end(), [](const OtoEntry &e) {
        return e.alias() == "shared";
    });
    QVERIFY(sharedEntry != result.end());
    QCOMPARE(sharedEntry->consonant(), 500.0);
}

void TestMergeOto::testSkipStrategy()
{
    MergeOtoOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "shared", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList other;
    other.append(makeEntry("x.wav", "shared", 0.0, 500.0, 2000.0, 200.0, 80.0));
    other.append(makeEntry("y.wav", "only_other", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"otherOtoLoaded", true},
        {"otherOtoList", QVariant::fromValue(other)},
        {"mergeStrategy", (int)MergeOtoOptionWidget::Skip},
    });
    worker.doWork(src, result, secondSave, opts);

    // "shared" skipped (original kept), "only_other" appended
    QCOMPARE(result.size(), 2);
    auto sharedEntry = std::find_if(result.begin(), result.end(), [](const OtoEntry &e) {
        return e.alias() == "shared";
    });
    QVERIFY(sharedEntry != result.end());
    QCOMPARE(sharedEntry->consonant(), 300.0); // original kept
}

void TestMergeOto::testKeepAllStrategy()
{
    MergeOtoOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "shared", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList other;
    other.append(makeEntry("x.wav", "shared", 0.0, 500.0, 2000.0, 200.0, 80.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"otherOtoLoaded", true},
        {"otherOtoList", QVariant::fromValue(other)},
        {"mergeStrategy", (int)MergeOtoOptionWidget::KeepAll},
    });
    worker.doWork(src, result, secondSave, opts);

    // KeepAll appends even duplicates → 2 entries both with alias "shared"
    QCOMPARE(result.size(), 2);
}

void TestMergeOto::testEmptyOtherList()
{
    MergeOtoOtoListModifyWorker worker;
    auto src = makeCvVoicebank();

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"otherOtoLoaded", true},
        {"otherOtoList", QVariant::fromValue(OtoEntryList{})},
        {"mergeStrategy", (int)MergeOtoOptionWidget::Replace},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
}

void TestMergeOto::testNotLoadedThrows()
{
    MergeOtoOtoListModifyWorker worker;
    OtoEntryList src, result, secondSave;
    auto opts = makeOptions({
        {"otherOtoLoaded", false},
        {"mergeStrategy", (int)MergeOtoOptionWidget::Replace},
    });

    QVERIFY_THROWS_EXCEPTION(ToolException, worker.doWork(src, result, secondSave, opts));
}

void TestMergeOto::testEmptyInput()
{
    MergeOtoOtoListModifyWorker worker;
    OtoEntryList other;
    other.append(makeEntry("x.wav", "entry", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"otherOtoLoaded", true},
        {"otherOtoList", QVariant::fromValue(other)},
        {"mergeStrategy", (int)MergeOtoOptionWidget::Replace},
    });
    worker.doWork({}, result, secondSave, opts);

    QCOMPARE(result.size(), 1);
    QCOMPARE(result.at(0).alias(), QString("entry"));
}

QTEST_MAIN(TestMergeOto)
#include "tst_mergeOto.moc"
