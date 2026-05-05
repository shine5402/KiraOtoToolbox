#include <QtTest>

#include "notdoanything/NotDoAnythingOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestNotDoAnything : public QObject
{
    Q_OBJECT
private slots:
    void testWorkerIdentity();
    void testWorkerEmptyInput();
    void testWorkerPreservesAllFields();
    void testWorkerWithSchemeData();
};

void TestNotDoAnything::testWorkerIdentity()
{
    NotDoAnythingOtoListModifyWorker worker;
    OtoEntryList src = makeCvVoicebank();
    OtoEntryList result, secondSave;

    worker.doWork(src, result, secondSave, {});

    QCOMPARE(result.size(), src.size());
    for (int i = 0; i < src.size(); ++i) {
        QVERIFY(result.at(i) == src.at(i));
    }
}

void TestNotDoAnything::testWorkerEmptyInput()
{
    NotDoAnythingOtoListModifyWorker worker;
    OtoEntryList result, secondSave;

    worker.doWork({}, result, secondSave, {});

    QVERIFY(result.isEmpty());
}

void TestNotDoAnything::testWorkerPreservesAllFields()
{
    NotDoAnythingOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("test.wav", "あ", 100.0, 300.0, 1200.0, 150.0, 50.0));

    OtoEntryList result, secondSave;
    worker.doWork(src, result, secondSave, {});

    QCOMPARE(result.size(), 1);
    QCOMPARE(result.at(0).fileName(), QString("test.wav"));
    QCOMPARE(result.at(0).alias(), QString("あ"));
    QCOMPARE(result.at(0).left(), 100.0);
    QCOMPARE(result.at(0).consonant(), 300.0);
    QCOMPARE(result.at(0).right(), 1200.0);
    QCOMPARE(result.at(0).preUtterance(), 150.0);
    QCOMPARE(result.at(0).overlap(), 50.0);
}

void TestNotDoAnything::testWorkerWithSchemeData()
{
    NotDoAnythingOtoListModifyWorker worker;

    auto testScheme = [&](const OtoEntryList &src) {
        OtoEntryList result, secondSave;
        worker.doWork(src, result, secondSave, {});
        QCOMPARE(result.size(), src.size());
        for (int i = 0; i < src.size(); ++i) {
            QVERIFY(result.at(i) == src.at(i));
        }
    };

    testScheme(makeVcvVoicebank());
    testScheme(makeCvvcVoicebank());
    testScheme(makeCvVvVoicebank());
}

QTEST_MAIN(TestNotDoAnything)
#include "tst_notDoAnything.moc"
