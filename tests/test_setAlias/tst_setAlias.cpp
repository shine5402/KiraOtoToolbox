#include <QtTest>

#include "setAlias/SetAliasOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestSetAlias : public QObject
{
    Q_OBJECT
private slots:
    void testPercentA_fullAlias();
    void testPercentA_minusDigitSuffix();
    void testPercentF_filenameWithoutExt();
    void testPercentS_digitSuffix();
    void testPercentR_dedupFirst();
    void testPercentR_dedupSubsequent();
    void testCutHeadCount();
    void testCutTailCount();
    void testStrShouldRemove_plain();
    void testStrShouldRemove_regex();
    void testOnlyForEmpty_skipsNonEmpty();
    void testOnlyForEmpty_allowsEmpty();
    void testEmptyInput();
    void testEmptyRenamingRule();
    void testCombinedPlaceholders();
};

void TestSetAlias::testPercentA_fullAlias()
{
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "hello", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "%a"},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("hello"));
}

void TestSetAlias::testPercentA_minusDigitSuffix()
{
    // When %s is present, %a = alias minus digit suffix
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "hello2", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "%a_%s"},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("hello_2"));
}

void TestSetAlias::testPercentF_filenameWithoutExt()
{
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("mysound.wav", "old", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "%f"},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("mysound"));
}

void TestSetAlias::testPercentS_digitSuffix()
{
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "entry5", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "%s"},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("5"));
}

void TestSetAlias::testPercentR_dedupFirst()
{
    // %r replaces with deduplication number. Identical working aliases get differentiated.
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a1.wav", "dup", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("a2.wav", "dup", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "%a%r"},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // Both entries have same input alias; %r must differentiate them
    QVERIFY(result.at(0).alias() != result.at(1).alias());
    // Each should contain the original alias "dup"
    QVERIFY(result.at(0).alias().contains("dup"));
    QVERIFY(result.at(1).alias().contains("dup"));
}

void TestSetAlias::testPercentR_dedupSubsequent()
{
    // %r with multiple duplicates and a unique entry
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a1.wav", "dup", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("a2.wav", "dup", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("a3.wav", "dup", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("a4.wav", "uniq", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "%a%r"},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // Three dup entries should be differentiated from each other
    QVERIFY(result.at(0).alias() != result.at(1).alias());
    QVERIFY(result.at(1).alias() != result.at(2).alias());
    QVERIFY(result.at(0).alias() != result.at(2).alias());
    // Unique entry should contain the original alias "uniq"
    QVERIFY(result.at(3).alias().contains("uniq"));
}

void TestSetAlias::testCutHeadCount()
{
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "prefix_alias", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "%a"},
        {"cutHeadCount", 7},
        {"cutTailCount", 0},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("alias"));
}

void TestSetAlias::testCutTailCount()
{
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "alias_suffix", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "%a"},
        {"cutHeadCount", 0},
        {"cutTailCount", 7},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("alias"));
}

void TestSetAlias::testStrShouldRemove_plain()
{
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "delete_this_part", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "%a"},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", "this_"},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("delete_part"));
}

void TestSetAlias::testStrShouldRemove_regex()
{
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "abc123def", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "%a"},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", "\\d+"},
        {"strShouldRemoveIsRegex", true},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("abcdef"));
}

void TestSetAlias::testOnlyForEmpty_skipsNonEmpty()
{
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "keep", 0.0, 300.0, 1000.0, 150.0, 50.0));
    src.append(makeEntry("b.wav", "", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "renamed"},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", true},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("keep"));
    QCOMPARE(result.at(1).alias(), QString("renamed"));
}

void TestSetAlias::testOnlyForEmpty_allowsEmpty()
{
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "old", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "new"},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString("new"));
}

void TestSetAlias::testEmptyInput()
{
    SetAliasOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "%a"},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork({}, result, secondSave, opts);

    QVERIFY(result.isEmpty());
}

void TestSetAlias::testEmptyRenamingRule()
{
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "hello", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", ""},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).alias(), QString(""));
}

void TestSetAlias::testCombinedPlaceholders()
{
    SetAliasOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("sound.wav", "entry3", 0.0, 300.0, 1000.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"renamingRule", "%f_%a_p%s"},
        {"cutHeadCount", 0},
        {"cutTailCount", 0},
        {"strShouldRemove", ""},
        {"strShouldRemoveIsRegex", false},
        {"onlyForEmpty", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // %f = sound, %a = entry (digit suffix removed because %s present), %s = 3
    QCOMPARE(result.at(0).alias(), QString("sound_entry_p3"));
}

QTEST_MAIN(TestSetAlias)
#include "tst_setAlias.moc"
