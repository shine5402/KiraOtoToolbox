#include <QtTest>

#include "removeAffix/RemoveAffixOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestRemoveAffix : public QObject
{
    Q_OBJECT
private slots:
    void testRemovePrefix();
    void testRemoveSuffix();
    void testRemoveBothPrefixAndSuffix();
    void testNoRemovalWhenDisabled();
    void testEmptyInput();
};

void TestRemoveAffix::testRemovePrefix()
{
    RemoveAffixOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "pre_hello", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"removePrefix", true},
        {"prefixList", QStringList{"pre_"}},
        {"removeSuffix", false},
        {"suffixList", QStringList{}},
        {"removePitchAffix", false},
        {"removePitchPrefix", false},
        {"removePitchSuffix", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("hello"));
}

void TestRemoveAffix::testRemoveSuffix()
{
    RemoveAffixOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "hello_suf", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"removePrefix", false},
        {"prefixList", QStringList{}},
        {"removeSuffix", true},
        {"suffixList", QStringList{"_suf"}},
        {"removePitchAffix", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("hello"));
}

void TestRemoveAffix::testRemoveBothPrefixAndSuffix()
{
    RemoveAffixOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "pre_hello_suf", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"removePrefix", true},
        {"prefixList", QStringList{"pre_"}},
        {"removeSuffix", true},
        {"suffixList", QStringList{"_suf"}},
        {"removePitchAffix", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // Specific affix removal runs first, then pitch removal
    QCOMPARE(result.at(0).alias(), QString("hello"));
}

void TestRemoveAffix::testNoRemovalWhenDisabled()
{
    RemoveAffixOtoListModifyWorker worker;
    OtoEntryList src = makeCvVoicebank();

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"removePrefix", false},
        {"prefixList", QStringList{}},
        {"removeSuffix", false},
        {"suffixList", QStringList{}},
        {"removePitchAffix", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
    for (int i = 0; i < src.size(); ++i) {
        QCOMPARE(result.at(i).alias(), src.at(i).alias());
    }
}

void TestRemoveAffix::testEmptyInput()
{
    RemoveAffixOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"removePrefix", true},
        {"prefixList", QStringList{"x"}},
        {"removeSuffix", false},
        {"suffixList", QStringList{}},
        {"removePitchAffix", false},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestRemoveAffix)
#include "tst_removeAffix.moc"
