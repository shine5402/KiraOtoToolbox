#include <QtTest>

#include <QDir>
#include <QTextCodec>

#include "otoUtils/OtoFileReader.h"

class TestOtoFileReader : public QObject
{
    Q_OBJECT
private:
    QString writeTempFile(const QString &content)
    {
        static int counter = 0;
        auto path = QDir::tempPath() + "/test_oto_" + QString::number(++counter) + ".ini";
        QFile file(path);
        (void)file.open(QFile::WriteOnly | QFile::Text);
        file.write(content.toUtf8());
        file.close();
        return path;
    }

    QString writeTempFileShiftJIS(const QString &content)
    {
        static int counter = 0;
        auto path = QDir::tempPath() + "/test_oto_sjis_" + QString::number(++counter) + ".ini";
        QFile file(path);
        (void)file.open(QFile::WriteOnly);
        file.write(QTextCodec::codecForName("Shift-JIS")->fromUnicode(content));
        file.close();
        return path;
    }

    void removeTempFile(const QString &path)
    {
        QFile::remove(path);
    }

    OtoFileReader makeReader(const QString &path)
    {
        OtoFileReader reader(path);
        reader.setTextCodec(QTextCodec::codecForName("UTF-8"));
        return reader;
    }

    OtoFileReader makeShiftJISReader(const QString &path)
    {
        OtoFileReader reader(path);
        reader.setTextCodec(QTextCodec::codecForName("Shift-JIS"));
        return reader;
    }

private slots:
    void testEmptyFile();
    void testAllValidLines();
    void testInvalidLines_data();
    void testInvalidLines();
    void testMixedValidAndInvalid();
    void testKeepInvalid();
    void testNonexistentFile();

    // Empty-field handling (setParam placeholder entries)
    void testAllFieldsEmpty();
    void testPartialEmptyFields();
    void testWhitespaceOnlyFields();

    // Shift-JIS encoding tests
    void testShiftJISJapaneseAlias();
    void testShiftJISJapaneseFilename();
    void testShiftJISVcvEntry();
    void testShiftJISMultipleEntries();
};

void TestOtoFileReader::testEmptyFile()
{
    auto path = writeTempFile("");
    auto reader = makeReader(path);
    auto entries = reader.read();
    QVERIFY(entries.isEmpty());
    QVERIFY(reader.readErrors().isEmpty());
    removeTempFile(path);
}

void TestOtoFileReader::testAllValidLines()
{
    auto path = writeTempFile(
        "test.wav=あ,0,300,1200,150,0\n"
        "test2.wav=a,100,400,1300,200,50\n");
    auto reader = makeReader(path);
    auto entries = reader.read();
    QCOMPARE(entries.size(), 2);
    QCOMPARE(entries[0].fileName(), QString("test.wav"));
    QCOMPARE(entries[1].fileName(), QString("test2.wav"));
    QVERIFY(reader.readErrors().isEmpty());
    removeTempFile(path);
}

void TestOtoFileReader::testInvalidLines_data()
{
    QTest::addColumn<QString>("line");
    QTest::addColumn<OtoEntry::OtoEntryError>("expectedError");
    QTest::addColumn<int>("expectedLineNumber");

    QTest::newRow("no equals sign") << "justSomeText" << OtoEntry::FileNameSeparatorNotFound << 1;
    QTest::newRow("empty filename before equals") << "=alias,0,0,0,0,0" << OtoEntry::EmptyFileName << 1;
    QTest::newRow("non-numeric left") << "test.wav=alias,abc,300,1200,150,0" << OtoEntry::LeftConvertFailed << 1;
    QTest::newRow("non-numeric consonant") << "test.wav=alias,0,abc,1200,150,0" << OtoEntry::ConsonantConvertFailed << 1;
    QTest::newRow("non-numeric right") << "test.wav=alias,0,300,abc,150,0" << OtoEntry::RightConvertFailed << 1;
    QTest::newRow("non-numeric preutterance") << "test.wav=alias,0,300,1200,abc,0" << OtoEntry::PreUtteranceConvertFailed << 1;
    QTest::newRow("non-numeric overlap") << "test.wav=alias,0,300,1200,150,abc" << OtoEntry::OverlapConvertFailed << 1;
}

void TestOtoFileReader::testInvalidLines()
{
    QFETCH(QString, line);
    QFETCH(OtoEntry::OtoEntryError, expectedError);
    QFETCH(int, expectedLineNumber);

    auto path = writeTempFile(line);
    auto reader = makeReader(path);
    auto entries = reader.read();
    QVERIFY(entries.isEmpty());
    QCOMPARE(reader.readErrors().size(), 1);
    QCOMPARE(reader.readErrors()[0].lineNumber, expectedLineNumber);
    QCOMPARE(reader.readErrors()[0].content, line);
    QCOMPARE(reader.readErrors()[0].error, expectedError);
    removeTempFile(path);
}

void TestOtoFileReader::testMixedValidAndInvalid()
{
    auto path = writeTempFile(
        "valid.wav=alias,0,300,1200,150,0\n"
        "invalid_line_no_equals\n"
        "valid2.wav=a,100,400,1300,200,50\n"
        "bad.wav=alias,xyz,0,0,0,0\n");
    auto reader = makeReader(path);
    auto entries = reader.read();
    QCOMPARE(entries.size(), 2);
    QCOMPARE(entries[0].fileName(), QString("valid.wav"));
    QCOMPARE(entries[1].fileName(), QString("valid2.wav"));

    QCOMPARE(reader.readErrors().size(), 2);
    QCOMPARE(reader.readErrors()[0].lineNumber, 2);
    QCOMPARE(reader.readErrors()[0].content, QString("invalid_line_no_equals"));
    QCOMPARE(reader.readErrors()[0].error, OtoEntry::FileNameSeparatorNotFound);

    QCOMPARE(reader.readErrors()[1].lineNumber, 4);
    QCOMPARE(reader.readErrors()[1].content, QString("bad.wav=alias,xyz,0,0,0,0"));
    QCOMPARE(reader.readErrors()[1].error, OtoEntry::LeftConvertFailed);
    removeTempFile(path);
}

void TestOtoFileReader::testKeepInvalid()
{
    auto path = writeTempFile(
        "valid.wav=alias,0,300,1200,150,0\n"
        "not_an_oto_line\n");
    auto reader = makeReader(path);
    reader.setKeepInvalid(true);
    auto entries = reader.read();
    QCOMPARE(entries.size(), 2);
    QCOMPARE(entries[0].fileName(), QString("valid.wav"));
    QCOMPARE(entries[1].fileName(), QString());
    QVERIFY(reader.readErrors().isEmpty());
    removeTempFile(path);
}

void TestOtoFileReader::testNonexistentFile()
{
    OtoFileReader reader("/nonexistent/path/oto.ini");
    auto entries = reader.read();
    QVERIFY(entries.isEmpty());
    QVERIFY(reader.readErrors().isEmpty());
}

// setParam writes placeholder entries with every numeric field empty. These
// must parse transparently as 0 rather than being skipped as errors.
void TestOtoFileReader::testAllFieldsEmpty()
{
    auto path = writeTempFile("_あ?あ.wav=,,,,,\n");
    auto reader = makeReader(path);
    auto entries = reader.read();
    QCOMPARE(entries.size(), 1);
    QCOMPARE(entries[0].fileName(), QString("_あ?あ.wav"));
    QVERIFY(entries[0].alias().isEmpty());
    QCOMPARE(entries[0].left(), 0.0);
    QCOMPARE(entries[0].consonant(), 0.0);
    QCOMPARE(entries[0].right(), 0.0);
    QCOMPARE(entries[0].preUtterance(), 0.0);
    QCOMPARE(entries[0].overlap(), 0.0);
    QVERIFY(reader.readErrors().isEmpty());
    removeTempFile(path);
}

// Empty numeric fields mixed with populated ones must also be treated as 0.
void TestOtoFileReader::testPartialEmptyFields()
{
    auto path = writeTempFile("test.wav=alias,,300,,150,\n");
    auto reader = makeReader(path);
    auto entries = reader.read();
    QCOMPARE(entries.size(), 1);
    QCOMPARE(entries[0].alias(), QString("alias"));
    QCOMPARE(entries[0].left(), 0.0);
    QCOMPARE(entries[0].consonant(), 300.0);
    QCOMPARE(entries[0].right(), 0.0);
    QCOMPARE(entries[0].preUtterance(), 150.0);
    QCOMPARE(entries[0].overlap(), 0.0);
    QVERIFY(reader.readErrors().isEmpty());
    removeTempFile(path);
}

// Whitespace-only numeric fields must be treated as 0 as well.
void TestOtoFileReader::testWhitespaceOnlyFields()
{
    auto path = writeTempFile("test.wav=alias, , 300 , , 150 , \n");
    auto reader = makeReader(path);
    auto entries = reader.read();
    QCOMPARE(entries.size(), 1);
    QCOMPARE(entries[0].left(), 0.0);
    QCOMPARE(entries[0].consonant(), 300.0);
    QCOMPARE(entries[0].right(), 0.0);
    QCOMPARE(entries[0].preUtterance(), 150.0);
    QCOMPARE(entries[0].overlap(), 0.0);
    QVERIFY(reader.readErrors().isEmpty());
    removeTempFile(path);
}

// Shift-JIS: entry with Japanese alias (typical solo-tone vowel entry)
void TestOtoFileReader::testShiftJISJapaneseAlias()
{
    auto path = writeTempFileShiftJIS("あ.wav=あ,0,300,1200,150,0\n");
    auto reader = makeShiftJISReader(path);
    auto entries = reader.read();
    QCOMPARE(entries.size(), 1);
    QCOMPARE(entries[0].fileName(), QString("あ.wav"));
    QCOMPARE(entries[0].alias(), QString("あ"));
    QCOMPARE(entries[0].left(), 0.0);
    QCOMPARE(entries[0].consonant(), 300.0);
    QCOMPARE(entries[0].right(), 1200.0);
    QCOMPARE(entries[0].preUtterance(), 150.0);
    QCOMPARE(entries[0].overlap(), 0.0);
    QVERIFY(reader.readErrors().isEmpty());
    removeTempFile(path);
}

// Shift-JIS: entry with Japanese filename
void TestOtoFileReader::testShiftJISJapaneseFilename()
{
    auto path = writeTempFileShiftJIS("あいう.wav=test_alias,100,200,300,400,50\n");
    auto reader = makeShiftJISReader(path);
    auto entries = reader.read();
    QCOMPARE(entries.size(), 1);
    QCOMPARE(entries[0].fileName(), QString("あいう.wav"));
    QCOMPARE(entries[0].alias(), QString("test_alias"));
    QCOMPARE(entries[0].left(), 100.0);
    QVERIFY(reader.readErrors().isEmpty());
    removeTempFile(path);
}

// Shift-JIS: VCV-style entry with leading vowel + kana alias
void TestOtoFileReader::testShiftJISVcvEntry()
{
    auto path = writeTempFileShiftJIS("あ_C4.wav=- あC4,0,300,1400,100,0\n");
    auto reader = makeShiftJISReader(path);
    auto entries = reader.read();
    QCOMPARE(entries.size(), 1);
    QCOMPARE(entries[0].fileName(), QString("あ_C4.wav"));
    QCOMPARE(entries[0].alias(), QString("- あC4"));
    QCOMPARE(entries[0].left(), 0.0);
    QCOMPARE(entries[0].consonant(), 300.0);
    QCOMPARE(entries[0].right(), 1400.0);
    QCOMPARE(entries[0].preUtterance(), 100.0);
    QCOMPARE(entries[0].overlap(), 0.0);
    QVERIFY(reader.readErrors().isEmpty());
    removeTempFile(path);
}

// Shift-JIS: multiple entries with mixed Japanese/ASCII content
void TestOtoFileReader::testShiftJISMultipleEntries()
{
    auto path = writeTempFileShiftJIS(
        "あ.wav=あ,0,300,1200,150,0\n"
        "か.wav=か,300,500,1400,500,-100\n"
        "き.wav=き,200,450,1300,450,50\n");
    auto reader = makeShiftJISReader(path);
    auto entries = reader.read();
    QCOMPARE(entries.size(), 3);
    QCOMPARE(entries[0].fileName(), QString("あ.wav"));
    QCOMPARE(entries[0].alias(), QString("あ"));
    QCOMPARE(entries[0].consonant(), 300.0);
    QCOMPARE(entries[0].overlap(), 0.0);

    QCOMPARE(entries[1].fileName(), QString("か.wav"));
    QCOMPARE(entries[1].alias(), QString("か"));
    QCOMPARE(entries[1].consonant(), 500.0);
    QCOMPARE(entries[1].overlap(), -100.0);

    QCOMPARE(entries[2].fileName(), QString("き.wav"));
    QCOMPARE(entries[2].alias(), QString("き"));
    QCOMPARE(entries[2].consonant(), 450.0);
    QCOMPARE(entries[2].overlap(), 50.0);

    QVERIFY(reader.readErrors().isEmpty());
    removeTempFile(path);
}

QTEST_APPLESS_MAIN(TestOtoFileReader)
#include "tst_otoFileReader.moc"
