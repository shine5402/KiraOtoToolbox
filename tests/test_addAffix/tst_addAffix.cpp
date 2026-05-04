#include <QtTest>

#include "addAffix/AddAffixOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestAddAffix : public QObject
{
    Q_OBJECT
private slots:
    void testPrefixOnly();
    void testSuffixOnly();
    void testPrefixAndSuffix();
    void testEmptyAffixIdentity();
    void testUnicodeAffix();
    void testPreservesNonAliasFields();
    void testEmptyInput();
};

void TestAddAffix::testPrefixOnly()
{
    AddAffixOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({{"prefix", "pre_"}, {"suffix", ""}});
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), 1);
    QCOMPARE(result.at(0).alias(), QString("pre_test"));
}

void TestAddAffix::testSuffixOnly()
{
    AddAffixOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({{"prefix", ""}, {"suffix", "_end"}});
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("test_end"));
}

void TestAddAffix::testPrefixAndSuffix()
{
    AddAffixOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "alias", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({{"prefix", "["}, {"suffix", "]"}});
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("[alias]"));
}

void TestAddAffix::testEmptyAffixIdentity()
{
    AddAffixOtoListModifyWorker worker;
    OtoEntryList src = makeCvVoicebank();
    OtoEntryList result, secondSave;
    auto opts = makeOptions({{"prefix", ""}, {"suffix", ""}});
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
    for (int i = 0; i < src.size(); ++i) {
        QCOMPARE(result.at(i).alias(), src.at(i).alias());
        QCOMPARE(result.at(i).left(), src.at(i).left());
        QCOMPARE(result.at(i).consonant(), src.at(i).consonant());
    }
}

void TestAddAffix::testUnicodeAffix()
{
    AddAffixOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "か", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({{"prefix", "開始"}, {"suffix", "終了"}});
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("開始か終了"));
}

void TestAddAffix::testPreservesNonAliasFields()
{
    AddAffixOtoListModifyWorker worker;
    OtoEntryList src = makeVcvVoicebank();
    OtoEntryList result, secondSave;
    auto opts = makeOptions({{"prefix", "P_"}, {"suffix", "_S"}});
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
    for (int i = 0; i < src.size(); ++i) {
        QCOMPARE(result.at(i).fileName(), src.at(i).fileName());
        QCOMPARE(result.at(i).left(), src.at(i).left());
        QCOMPARE(result.at(i).consonant(), src.at(i).consonant());
        QCOMPARE(result.at(i).right(), src.at(i).right());
        QCOMPARE(result.at(i).preUtterance(), src.at(i).preUtterance());
        QCOMPARE(result.at(i).overlap(), src.at(i).overlap());
        // alias should have affix applied
        QCOMPARE(result.at(i).alias(), QString("P_" + src.at(i).alias() + "_S"));
    }
}

void TestAddAffix::testEmptyInput()
{
    AddAffixOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({{"prefix", "x"}, {"suffix", "y"}});
    worker.doWork({}, result, secondSave, opts);

    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestAddAffix)
#include "tst_addAffix.moc"
