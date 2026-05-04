#include <QtTest>
#include <QTemporaryDir>
#include <QFile>
#include <QTextStream>

#include "convertPlusMinusRight/ConvertPlusMinusRightOtoListModifyWorker.h"
#include "OtoTestUtils.h"

class TestConvertPlusMinusRight : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void testConvertToPositive();
    void testConvertToNegative();
    void testFileNotFound();
    void testEmptyInput();

private:
    QTemporaryDir tmpDir;
    QString otoFilePath;
};

void TestConvertPlusMinusRight::initTestCase()
{
    QVERIFY(tmpDir.isValid());
    // Copy fixture WAV into temp dir
    QString fixturePath = QStringLiteral(FIXTURE_DIR "/LJ001-0001.wav");
    QString wavPath = tmpDir.filePath("LJ001-0001.wav");
    QVERIFY(QFile::copy(fixturePath, wavPath));

    // Create a dummy oto.ini in the same dir
    otoFilePath = tmpDir.filePath("oto.ini");
    QFile otoFile(otoFilePath);
    QVERIFY(otoFile.open(QIODevice::WriteOnly | QIODevice::Text));
    QTextStream out(&otoFile);
    out << "LJ001-0001.wav=test,100.0,300.0,-50.0,200.0,50.0\n";
    otoFile.close();
}

void TestConvertPlusMinusRight::testConvertToPositive()
{
    ConvertPlusMinusRightOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("LJ001-0001.wav", "test", 100.0, 300.0, -50.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"load/fileName", otoFilePath},
        {"savePositive", true},
        {"saveNegative", false},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // Right should be converted from negative to positive
    QVERIFY(result.at(0).right() > 0);
}

void TestConvertPlusMinusRight::testConvertToNegative()
{
    ConvertPlusMinusRightOtoListModifyWorker worker;
    OtoEntryList src;
    // Use a positive right value first, then convert to negative
    src.append(makeEntry("LJ001-0001.wav", "test", 100.0, 300.0, 500.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"load/fileName", otoFilePath},
        {"savePositive", false},
        {"saveNegative", true},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork(src, result, secondSave, opts);

    // Right should be converted from positive to negative
    QVERIFY(result.at(0).right() < 0);
}

void TestConvertPlusMinusRight::testFileNotFound()
{
    ConvertPlusMinusRightOtoListModifyWorker worker;
    OtoEntryList src;
    src.append(makeEntry("nonexistent.wav", "test", 100.0, 300.0, 1000.0, 200.0, 50.0));

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"load/fileName", "/tmp/nonexistent_dir/nonexistent.ini"},
        {"savePositive", true},
        {"saveNegative", false},
        {"interpretBySystemEncoding", false},
    });

    QVERIFY_THROWS_EXCEPTION(ToolException, worker.doWork(src, result, secondSave, opts));
}

void TestConvertPlusMinusRight::testEmptyInput()
{
    ConvertPlusMinusRightOtoListModifyWorker worker;
    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"load/fileName", otoFilePath},
        {"savePositive", true},
        {"saveNegative", false},
        {"interpretBySystemEncoding", false},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestConvertPlusMinusRight)
#include "tst_convertPlusMinusRight.moc"
