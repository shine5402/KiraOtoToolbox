#include <QtTest>

#include "jsScript/JavaScriptToolOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestJsScript : public QObject
{
    Q_OBJECT
private slots:
    void testModifyAlias();
    void testModifyField();
    void testEmptyScript_preservesData();
    void testReturnDataLength();
    void testEmptyInput();
};

void TestJsScript::testModifyAlias()
{
    JavaScriptToolOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "old", 100.0, 300.0, 1000.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"script", "data[0].alias = 'new';"},
        {"load/fileName", "/tmp/dummy.ini"},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), 1);
    QCOMPARE(result.at(0).alias(), QString("new"));
}

void TestJsScript::testModifyField()
{
    JavaScriptToolOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "test", 100.0, 300.0, 1000.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"script", "data[0].left = 500.0; data[0].consonant = 600.0;"},
        {"load/fileName", "/tmp/dummy.ini"},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.at(0).left(), 500.0);
    QCOMPARE(result.at(0).consonant(), 600.0);
}

void TestJsScript::testEmptyScript_preservesData()
{
    JavaScriptToolOtoListModifyWorker worker;
    auto src = makeCvVoicebank();

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"script", ""},
        {"load/fileName", "/tmp/dummy.ini"},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
    for (int i = 0; i < src.size(); ++i)
        QVERIFY(result.at(i) == src.at(i));
}

void TestJsScript::testReturnDataLength()
{
    JavaScriptToolOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("a.wav", "a", 100.0, 300.0, 1000.0, 200.0, 50.0));
    src.append(makeEntry("b.wav", "b", 100.0, 300.0, 1000.0, 200.0, 50.0));
    src.append(makeEntry("c.wav", "c", 100.0, 300.0, 1000.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"script", "// keep all three entries unchanged"},
        {"load/fileName", "/tmp/dummy.ini"},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), 3);
}

void TestJsScript::testEmptyInput()
{
    JavaScriptToolOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"script", "// empty input, nothing to do"},
        {"load/fileName", "/tmp/dummy.ini"},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestJsScript)
#include "tst_jsScript.moc"
