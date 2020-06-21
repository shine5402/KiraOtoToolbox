#include <QtTest>

#include <otoentry.h>
#include <otofilereader.h>
#include <QMetaEnum>

class OtoUtilTest : public QObject
{
    Q_OBJECT

public:
    OtoUtilTest();
    ~OtoUtilTest();
private:
    void prepareNormalData();;
private slots:
    void construct_validTest();
    void construct_validTest_data(){
        prepareNormalData();
    }

    void construct_fileNameTest();
    void construct_fileNameTest_data(){
        prepareNormalData();
    }

    void construct_aliasTest();
    void construct_aliasTest_data(){
        prepareNormalData();
    }

    void construct_leftTest();
    void construct_leftTest_data(){
        prepareNormalData();
    }

    void construct_consonantTest();
    void construct_consonantTest_data(){
        prepareNormalData();
    }

    void construct_rightTest();
    void construct_rightTest_data(){
        prepareNormalData();
    }

    void construct_preUtteranceTest();
    void construct_preUtteranceTest_data(){
        prepareNormalData();
    }

    void construct_overlapTest();
    void construct_overlapTest_data(){
        prepareNormalData();
    }

    void construct_errorTest();
    void construct_errorTest_data();

    void toStringTest();
    void toStringTest_data(){
        prepareNormalData();
    }

    void fileReader_test();
    void fileReader_test_data();

    void fileReader_invalidTest();
    void fileReader_invalidTest_data();

    void fileReader_emptyTest();

    void fileReader_textCodecTest();
    void fileReader_textCodecTest_data();

    void pitchStringRangeTest();
    void pitchStringRangeTest_data();

    void removeSuffixTest();
    void removeSuffixTest_data();

    void removePitchSuffixTest();
    void removePitchSuffixTest_data();

    void getDigitalSuffixTest();
    void getDigitalSuffixTest_data();

    void parameterCountTest();
    void parameterOrderFlagConversionTest();
    void parameterValidFlagTest();

    void getParameterTest();
    void getParameterTest_data(){
        prepareNormalData();
    }
    
    void setParameterTest();

    void writeToFileTest();
};

OtoUtilTest::OtoUtilTest()
{

}

OtoUtilTest::~OtoUtilTest()
{

}

void OtoUtilTest::prepareNormalData(){
    QTest::addColumn<QString>("string");
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<QString>("alias");
    QTest::addColumn<double>("left");
    QTest::addColumn<double>("consonant");
    QTest::addColumn<double>("right");
    QTest::addColumn<double>("preUtterance");
    QTest::addColumn<double>("overlap");

    QTest::newRow("VCV_Start") << "_さんささすぃさすさ.wav=- さA#3,882.561,346.153,-538.461,230.769,76.923"
                               << "_さんささすぃさすさ.wav" << "- さA#3"
                               << 882.561 << 346.153 << -538.461 << 230.769 << 76.923;
    QTest::newRow("VCV_Middle") << "_さんささすぃさすさ.wav=a さA#3,2200.922,346.153,-538.461,230.769,76.923"
                                << "_さんささすぃさすさ.wav" << "a さA#3"
                                << 2200.922 << 346.153 << -538.461 << 230.769 << 76.923;
    QTest::newRow("End Breath") << "_あんああいあうあ.wav=a RA#3,4398.303,346.153,-538.461,230.769,76.923"
                                << "_あんああいあうあ.wav" << "a RA#3"
                                << 4398.303 << 346.153 << -538.461 << 230.769 << 76.923;
    QTest::newRow("CV") << "_さんささすぃさすさ.wav=さA#3,1890.084,197.355,-343.466,105.004,35.422"
                        << "_さんささすぃさすさ.wav" << "さA#3"
                        << 1890.084 << 197.355 << -343.466 << 105.004 << 35.422;
    QTest::newRow("VC") << "_さんささすぃさすさ.wav=a sA#3,2108.431,281.383,-320.601,230.769,76.922"
                        << "_さんささすぃさすさ.wav" << "a sA#3"
                        << 2108.431 << 281.383 << -320.601 << 230.769 << 76.922;
    QTest::newRow("End Breath with Chinese Character") << "_あ吸あ吐.wav=a 息RA#3,1492.559,459.849,-572.022,250.0,83.3"
                                                       << "_あ吸あ吐.wav" << "a 息RA#3"
                                                       << 1492.559 << 459.849 << -572.022 << 250.0 << 83.3;
    QTest::newRow("Edge") << "_う・う.wav=u ・A#3,786.058,264.828,-317.119,154.341,51.4"
                          << "_う・う.wav" << "u ・A#3"
                          << 786.058 << 264.828 << -317.119 << 154.341 << 51.4;
}

void OtoUtilTest::construct_validTest()
{
    QFETCH(QString, string);

    QVERIFY(OtoEntry(string).isValid());
}

void OtoUtilTest::construct_fileNameTest()
{
    QFETCH(QString, string);
    QFETCH(QString, fileName);

    OtoEntry otoEntry(string);

    Q_ASSERT(otoEntry.isValid());
    QCOMPARE(otoEntry.fileName(), fileName);
}


void OtoUtilTest::construct_aliasTest()
{
    QFETCH(QString, string);
    QFETCH(QString, alias);

    OtoEntry otoEntry(string);

    Q_ASSERT(otoEntry.isValid());
    QCOMPARE(otoEntry.alias(), alias);
}

void OtoUtilTest::construct_leftTest()
{
    QFETCH(QString, string);
    QFETCH(double, left);

    OtoEntry otoEntry(string);

    Q_ASSERT(otoEntry.isValid());
    QCOMPARE(otoEntry.left(), left);
}

void OtoUtilTest::construct_consonantTest()
{
    QFETCH(QString, string);
    QFETCH(double, consonant);

    OtoEntry otoEntry(string);

    Q_ASSERT(otoEntry.isValid());
    QCOMPARE(otoEntry.consonant(), consonant);
}

void OtoUtilTest::construct_rightTest()
{
    QFETCH(QString, string);
    QFETCH(double, right);

    OtoEntry otoEntry(string);

    Q_ASSERT(otoEntry.isValid());
    QCOMPARE(otoEntry.right(), right);
}

void OtoUtilTest::construct_preUtteranceTest()
{
    QFETCH(QString, string);
    QFETCH(double, preUtterance);

    OtoEntry otoEntry(string);

    Q_ASSERT(otoEntry.isValid());
    QCOMPARE(otoEntry.preUtterance(), preUtterance);
}

void OtoUtilTest::construct_overlapTest()
{
    QFETCH(QString, string);
    QFETCH(double, overlap);

    OtoEntry otoEntry(string);

    Q_ASSERT(otoEntry.isValid());
    QCOMPARE(otoEntry.overlap(), overlap);
}

void OtoUtilTest::construct_errorTest()
{
    QFETCH(QString, string);

    OtoEntry otoEntry(string);

    QVERIFY(!otoEntry.isValid());

    QFETCH(OtoEntry::OtoEntryError, errorCode);
    QFETCH(QString, errorString);

    QCOMPARE(otoEntry.error(), errorCode);
    QCOMPARE(otoEntry.errorString(), errorString);

}

void OtoUtilTest::construct_errorTest_data(){
    QTest::addColumn<QString>("string");
    QTest::addColumn<OtoEntry::OtoEntryError>("errorCode");
    QTest::addColumn<QString>("errorString");

    QTest::newRow("Blank String") << "" << OtoEntry::EmptyOtoString << "The provided string is empty";
    QTest::newRow("Empty FileName") << "=,149,201,-599,0,0" << OtoEntry::EmptyFileName << "The fileName is empty";
    QTest::newRow("No filename seperator") << "あ.wav,149,201,-599,0,0" << OtoEntry::FileNameSeparatorNotFound << "The separator between fileName and alias are not found.";
    QTest::newRow("Wrong left") << "あ.wav=,14q9,201,-599,0,0" << OtoEntry::LeftConvertFailed << "Convert left string to double failed.";
    QTest::newRow("Wrong consonant") << "あ.wav=,149,2a01,-599,0,0" << OtoEntry::ConsonantConvertFailed << "Convert consonant string to double failed.";
    QTest::newRow("Wrong right") << "あ.wav=,149,201,-5right9,0,0" << OtoEntry::RightConvertFailed << "Convert right string to double failed.";
    QTest::newRow("Wrong preUtterance") << "あ.wav=,149,201,-59,0preUtterance,0" << OtoEntry::PreUtteranceConvertFailed << "Convert preUtterance string to double failed.";
    QTest::newRow("Wrong overlap") << "あ.wav=,149,201,-59,0,0overlap" << OtoEntry::OverlapConvertFailed << "Convert overlap string to double failed.";
}

void OtoUtilTest::toStringTest()
{
    QFETCH(QString, string);

    OtoEntry otoEntry(string);

    Q_ASSERT(otoEntry.isValid());

    OtoEntry otoEntry2(otoEntry.toString());

    QVERIFY(otoEntry2.isValid());
    QCOMPARE(otoEntry, otoEntry2);
}

void OtoUtilTest::fileReader_test()
{
    QFETCH(QString, otofileName);
    QFETCH(int, otoCount);
    QFETCH(QStringList, content);

    OtoFileReader reader(otofileName);
    auto otoEntrys = reader.getEntryList();

    QCOMPARE(otoEntrys.count(), otoCount);
    for (int i = 0; i < otoCount; ++i){
        QCOMPARE(otoEntrys.at(i), OtoEntry(content.at(i)));
    }
}

void OtoUtilTest::fileReader_test_data()
{
    QTest::addColumn<QString>("otofileName");
    QTest::addColumn<int>("otoCount");
    QTest::addColumn<QStringList>("content");

    QTest::newRow("normalData") << ":/file2test/normalData.ini" << 7
                                << QStringList{"_さんささすぃさすさ.wav=- さA#3,882.561,346.153,-538.461,230.769,76.923",
                                   "_さんささすぃさすさ.wav=a さA#3,2200.922,346.153,-538.461,230.769,76.923",
                                   "_あんああいあうあ.wav=a RA#3,4398.303,346.153,-538.461,230.769,76.923",
                                   "_さんささすぃさすさ.wav=さA#3,1890.084,197.355,-343.466,105.004,35.422",
                                   "_さんささすぃさすさ.wav=a sA#3,2108.431,281.383,-320.601,230.769,76.922",
                                   "_あ吸あ吐.wav=a 息RA#3,1492.559,459.849,-572.022,250.0,83.3",
                                   "_う・う.wav=u ・A#3,786.058,264.828,-317.119,154.341,51.4"};
}

void OtoUtilTest::fileReader_invalidTest()
{
    QFETCH(QString, otofileName);
    QFETCH(int, otoCount);
    QFETCH(int, validCount);

    OtoFileReader reader(otofileName);
    auto otoEntrys = reader.getEntryList();

    QCOMPARE(otoEntrys.count(), validCount);

    reader.setKeepInvalid(true);

    auto otoEntrysKeepInvalid = reader.getEntryList();

    QCOMPARE(otoEntrysKeepInvalid.count(), otoCount);
}

void OtoUtilTest::fileReader_invalidTest_data()
{
    QTest::addColumn<QString>("otofileName");
    QTest::addColumn<int>("otoCount");
    QTest::addColumn<int>("validCount");

    QTest::newRow("All invalid data") << ":/file2test/errorData.ini" << 7 << 0;
}

void OtoUtilTest::fileReader_emptyTest()
{
    OtoFileReader reader(":/file2test/emptyFile.ini");

    auto entrys = reader.getEntryList();

    QCOMPARE(entrys.count(), 0);
}

void OtoUtilTest::fileReader_textCodecTest()
{
    QFETCH(QString, otofileName);
    QFETCH(QString, codecName);
    QFETCH(int, otoCount);
    QFETCH(QStringList, content);

    OtoFileReader reader(otofileName, QTextCodec::codecForName(codecName.toUtf8()));
    auto otoEntrys = reader.getEntryList();

    QCOMPARE(otoEntrys.count(), otoCount);
    for (int i = 0; i < otoCount; ++i){
        QCOMPARE(otoEntrys.at(i), OtoEntry(content.at(i)));
    }
}

void OtoUtilTest::fileReader_textCodecTest_data()
{
    QTest::addColumn<QString>("otofileName");
    QTest::addColumn<QString>("codecName");
    QTest::addColumn<int>("otoCount");
    QTest::addColumn<QStringList>("content");

    QTest::newRow("normalData") << ":/file2test/normalData_UTF-8.ini" << "UTF-8" << 7
                                << QStringList{"_さんささすぃさすさ.wav=- さA#3,882.561,346.153,-538.461,230.769,76.923",
                                   "_さんささすぃさすさ.wav=a さA#3,2200.922,346.153,-538.461,230.769,76.923",
                                   "_あんああいあうあ.wav=a RA#3,4398.303,346.153,-538.461,230.769,76.923",
                                   "_さんささすぃさすさ.wav=さA#3,1890.084,197.355,-343.466,105.004,35.422",
                                   "_さんささすぃさすさ.wav=a sA#3,2108.431,281.383,-320.601,230.769,76.922",
                                   "_あ吸あ吐.wav=a 息RA#3,1492.559,459.849,-572.022,250.0,83.3",
                                   "_う・う.wav=u ・A#3,786.058,264.828,-317.119,154.341,51.4"};

}

void OtoUtilTest::pitchStringRangeTest()
{
    QFETCH(QString,bottom);
    QFETCH(QString,top);
    QFETCH(QStringList, expect);
    QFETCH(int, characterCase);

    auto result = OtoEntryFunctions::getPitchStringRange(bottom, top, static_cast<OtoEntryFunctions::CharacterCase>(characterCase));

    auto getIntersection = [] (QList<QList<QString> > lists) -> QList<QString> {
        QHash<QString,int> counts;
            QList<QString> result;
            for (auto list : lists)
            {
                for (auto i : list)
                {
                    counts.insert(i,counts.value(i) + 1);
                }
            }
            for (auto it = counts.begin();it != counts.end();++it)
            {
                if (it.value() == lists.count())
                    result.append(it.key());
            }
            return result;
    };

    auto inter = getIntersection({result, expect});

    qDebug() << inter;
    qDebug() << expect;
    QCOMPARE(inter.count(), expect.count());

}

void OtoUtilTest::pitchStringRangeTest_data()
{
    QTest::addColumn<QString>("bottom");
    QTest::addColumn<QString>("top");
    QTest::addColumn<int>("characterCase");
    QTest::addColumn<QStringList>("expect");

    QTest::newRow("Same octave") << "C3" << "F3" << static_cast<int>(OtoEntryFunctions::Upper) << QStringList{"C3", "C#3", "D3", "D#3", "E3", "F3"};
    QTest::newRow("Same octave (negative)") << "C-3" << "F-3" << static_cast<int>(OtoEntryFunctions::Upper) << QStringList{"C-3", "C#-3", "D-3", "D#-3", "E-3", "F-3"};
    QTest::newRow("Same octave (double digit)") << "C13" << "F13" << static_cast<int>(OtoEntryFunctions::Upper) << QStringList{"C13", "C#13", "D13", "D#13", "E13", "F13"};
    QTest::newRow("Different octave") << "D3" << "D4" << static_cast<int>(OtoEntryFunctions::Upper) << QStringList{"D3","D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3", "C4", "C#4", "D4"};
    QTest::newRow("Different octave (negative to zero)") << "D-1" << "D0" << static_cast<int>(OtoEntryFunctions::Upper) << QStringList{"D-1", "D#-1", "E-1","F-1","F#-1","G-1","G#-1","A-1","A#-1","B-1","C0","C#0","D0"};

    QTest::newRow("Same octave, lower character") << "c3" << "f3" << static_cast<int>(OtoEntryFunctions::Lower) << QStringList{"c3", "c#3", "d3", "d#3", "e3", "f3"};
    QTest::newRow("Same octave (negative), lower character") << "c-3" << "f-3"  << static_cast<int>(OtoEntryFunctions::Lower) << QStringList{"c-3", "c#-3", "d-3", "d#-3", "e-3", "f-3"};
    QTest::newRow("Same octave (double digit), lower character") << "c13" << "f13"  << static_cast<int>(OtoEntryFunctions::Lower) << QStringList{"c13", "c#13", "d13", "d#13", "e13", "f13"};
    QTest::newRow("Different octave, lower character") << "d3" << "d4"  << static_cast<int>(OtoEntryFunctions::Lower) << QStringList{"d3","d#3", "e3", "f3", "f#3", "g3", "g#3", "a3", "a#3", "b3", "c4", "c#4", "d4"};
    QTest::newRow("Different octave (negative to zero), lower character") << "d-1" << "d0"  << static_cast<int>(OtoEntryFunctions::Lower) << QStringList{"d-1", "d#-1", "e-1","f-1","f#-1","g-1","g#-1","a-1","a#-1","b-1","c0","c#0","d0"};

}

void OtoUtilTest::removeSuffixTest()
{
    QFETCH(QString, src);
    QFETCH(QString, suffix);
    QFETCH(QString, expect);
    QFETCH(Qt::CaseSensitivity, cs);

    QCOMPARE(OtoEntryFunctions::removeSuffix(src, suffix, cs), expect);
}

void OtoUtilTest::removeSuffixTest_data()
{
    QTest::addColumn<QString>("src");
    QTest::addColumn<QString>("suffix");
    QTest::addColumn<Qt::CaseSensitivity>("cs");
    QTest::addColumn<QString>("expect");

    QTest::newRow("Pitch suffix") << "あF3" << "F3" << Qt::CaseSensitive << "あ";
    QTest::newRow("Number suffix") << "あ3" << "3" << Qt::CaseSensitive << "あ";
    QTest::newRow("Chinese character") << "a息" << "息" << Qt::CaseSensitive << "a";

    QTest::newRow("Pitch suffix, case insensitive") << "あF3" << "f3" << Qt::CaseInsensitive << "あ";
    QTest::newRow("char suffix, case insensitive") << "あF" << "f" << Qt::CaseInsensitive << "あ";
}

void OtoUtilTest::removePitchSuffixTest()
{
    QFETCH(QString, src);
    QFETCH(QString, bottomPitch);
    QFETCH(QString, topPitch);
    QFETCH(Qt::CaseSensitivity, cs);
    QFETCH(int, characterCase);
    auto characterCaseEnum = static_cast<OtoEntryFunctions::CharacterCase>(characterCase);
    QFETCH(QString, expect);
    QFETCH(QString, pitchToRemove);

    QString pitchToRemoveResult;

    QCOMPARE(OtoEntryFunctions::removePitchSuffix(src, bottomPitch, topPitch, cs, characterCaseEnum, &pitchToRemoveResult), expect);
    QCOMPARE(pitchToRemoveResult, pitchToRemove);
}

void OtoUtilTest::removePitchSuffixTest_data()
{
    QTest::addColumn<QString>("src");
    QTest::addColumn<QString>("bottomPitch");
    QTest::addColumn<QString>("topPitch");
    QTest::addColumn<Qt::CaseSensitivity>("cs");
    QTest::addColumn<int>("characterCase");
    QTest::addColumn<QString>("pitchToRemove");
    QTest::addColumn<QString>("expect");

    QTest::newRow("case sensitive, upper") << "aF3" << "C1" << "C6" << Qt::CaseSensitive << static_cast<int>(OtoEntryFunctions::Upper) << "F3" <<"a";
    QTest::newRow("case sensitive, upper, not match") << "af3" << "C1" << "C6" << Qt::CaseSensitive << static_cast<int>(OtoEntryFunctions::Upper) << "" << "af3";
    QTest::newRow("case insensitive, upper") << "af3" << "C1" << "C6" << Qt::CaseInsensitive << static_cast<int>(OtoEntryFunctions::Upper) << "F3" << "a";
    QTest::newRow("case sensitive, lower") << "af3" << "C1" << "C6" << Qt::CaseSensitive << static_cast<int>(OtoEntryFunctions::Lower) << "f3" << "a";
    QTest::newRow("case sensitive, lower, not match") << "aF3" << "C1" << "C6" << Qt::CaseSensitive << static_cast<int>(OtoEntryFunctions::Lower) << "" << "aF3";
    QTest::newRow("case insensitive, lower") << "aF3" << "C1" << "C6" << Qt::CaseInsensitive << static_cast<int>(OtoEntryFunctions::Lower) << "f3" << "a";

    QTest::newRow("case sensitive, upper, lower range input") << "aF3" << "c1" << "c6" << Qt::CaseSensitive << static_cast<int>(OtoEntryFunctions::Upper) << "F3" << "a";
    QTest::newRow("case sensitive, upper, not match, lower range input") << "af3" << "c1" << "c6" << Qt::CaseSensitive << static_cast<int>(OtoEntryFunctions::Upper) << "" << "af3";
    QTest::newRow("case insensitive, upper, lower range input") << "af3" << "c1" << "c6" << Qt::CaseInsensitive << static_cast<int>(OtoEntryFunctions::Upper) << "F3" << "a";
    QTest::newRow("case sensitive, lower, lower range input") << "af3" << "c1" << "c6" << Qt::CaseSensitive << static_cast<int>(OtoEntryFunctions::Lower) << "f3" << "a";
    QTest::newRow("case sensitive, lower, not match, lower range input") << "aF3" << "c1" << "c6" << Qt::CaseSensitive << static_cast<int>(OtoEntryFunctions::Lower) << "" << "aF3";
    QTest::newRow("case insensitive, lower, lower range input") << "aF3" << "c1" << "c6" << Qt::CaseInsensitive << static_cast<int>(OtoEntryFunctions::Lower) << "f3" << "a";

    QTest::newRow("range not match") << "aF3" << "A3" << "C4" << Qt::CaseSensitive << static_cast<int>(OtoEntryFunctions::Upper) << "" << "aF3";

    QTest::newRow("with #") << "aF#3" << "F3" << "G3" << Qt::CaseSensitive << static_cast<int>(OtoEntryFunctions::Upper) << "F#3" << "a";
}

void OtoUtilTest::getDigitalSuffixTest()
{
    QFETCH(QString, src);
    QFETCH(QString, expect);
    QFETCH(int, position);

    int resultPosition = -1;
    auto result = OtoEntryFunctions::getDigitSuffix(src, &resultPosition);

    QCOMPARE(result, expect);
    QCOMPARE(resultPosition, position);
}

void OtoUtilTest::getDigitalSuffixTest_data()
{
    QTest::addColumn<QString>("src");
    QTest::addColumn<QString>("expect");
    QTest::addColumn<int>("position");

    QTest::addRow("1 digit") << "a2" << "2" << 1;
    QTest::addRow("2 digit") << "a23" << "23" << 1;
    QTest::addRow("no digit") << "abc" << "" << -1;
}

void OtoUtilTest::parameterCountTest()
{
    static const int expectedCount = 7;
    auto metaObjOrder = QMetaEnum::fromType<OtoEntry::OtoParameterOrder>();
    auto metaObjFlag = QMetaEnum::fromType<OtoEntry::OtoParameter>();
    QCOMPARE(metaObjOrder.keyCount(), metaObjFlag.keyCount());
    QCOMPARE(metaObjOrder.keyCount(), expectedCount);
}

void OtoUtilTest::parameterOrderFlagConversionTest()
{
    auto metaObjOrder = QMetaEnum::fromType<OtoEntry::OtoParameterOrder>();
    auto metaObjFlag = QMetaEnum::fromType<OtoEntry::OtoParameter>();

    for (int i = 0; i < metaObjOrder.keyCount(); ++i){
        auto keyOrder = metaObjOrder.key(i);
        auto keyFlag = metaObjFlag.key(i);
        auto valueOrder = metaObjOrder.value(i);
        auto valueFlag = metaObjFlag.value(i);

        auto orderToFlag = OtoEntry::getParameterFlag(static_cast<OtoEntry::OtoParameterOrder>(valueOrder));
        auto orderToFlagKey  = metaObjFlag.valueToKey(orderToFlag);
        QCOMPARE(orderToFlagKey, keyFlag);

        auto flagToOrder = OtoEntry::getParameterOrder(static_cast<OtoEntry::OtoParameter>(valueFlag));
        auto flagToOrderKey = metaObjOrder.valueToKey(flagToOrder);
        QCOMPARE(flagToOrderKey, keyOrder);
    }
}

void OtoUtilTest::parameterValidFlagTest()
{
    auto metaObjFlag = QMetaEnum::fromType<OtoEntry::OtoParameter>();
    for (int i = 0; i < metaObjFlag.keyCount(); ++i){
        for (int j = 0; j < metaObjFlag.keyCount(); ++j){
            if (i == j)
                continue;
            QVERIFY(metaObjFlag.value(i) ^ metaObjFlag.value(j));
        }
    }
}

void OtoUtilTest::getParameterTest()
{
    QFETCH(QString, string);
    OtoEntry entry(string);
    QFETCH(QString, fileName);
    QFETCH(QString, alias);
    QFETCH(double, left);
    QFETCH(double, consonant);
    QFETCH(double, right);
    QFETCH(double, preUtterance);
    QFETCH(double, overlap);

    auto expectedFileName = entry.getParameter(OtoEntry::FileName);
    QCOMPARE(expectedFileName, fileName);
    auto expectedFileNameOrder = entry.getParameter(OtoEntry::FILENAME);
    QCOMPARE(expectedFileNameOrder, fileName);

    auto expectedAlias = entry.getParameter(OtoEntry::Alias);
    QCOMPARE(expectedAlias, alias);
    auto expectedAliasOrder = entry.getParameter(OtoEntry::ALIAS);
    QCOMPARE(expectedAliasOrder, alias);

    auto expectedLeft = entry.getParameter(OtoEntry::Left);
    QCOMPARE(expectedLeft, left);
    auto expectedLeftOrder = entry.getParameter(OtoEntry::LEFT);
    QCOMPARE(expectedLeftOrder, left);

    auto expectedConsonant = entry.getParameter(OtoEntry::Consonant);
    QCOMPARE(expectedConsonant, consonant);
    auto expectedConsonantOrder = entry.getParameter(OtoEntry::CONSONANT);
    QCOMPARE(expectedConsonantOrder, consonant);

    auto expectedRight = entry.getParameter(OtoEntry::Right);
    QCOMPARE(expectedRight, right);
    auto expectedRightOrder = entry.getParameter(OtoEntry::RIGHT);
    QCOMPARE(expectedRightOrder, right);

    auto expectedPreutterance = entry.getParameter(OtoEntry::PreUtterance);
    QCOMPARE(expectedPreutterance, preUtterance);
    auto expectedPreutteranceOrder = entry.getParameter(OtoEntry::PREUTTERANCE);
    QCOMPARE(expectedPreutteranceOrder, preUtterance);

    auto expectedOverlap = entry.getParameter(OtoEntry::Overlap);
    QCOMPARE(expectedOverlap, overlap);
    auto expectedOverlapOrder = entry.getParameter(OtoEntry::OVERLAP);
    QCOMPARE(expectedOverlapOrder, overlap);
}

void OtoUtilTest::setParameterTest()
{
    OtoEntry entry{"test.wav", "test", 0, 0, 0, 0, 0};
    
    entry.setParameter(OtoEntry::FileName, "test1.wav");
    QCOMPARE(entry.fileName(), "test1.wav");
    entry.setParameter(OtoEntry::FILENAME, "test2.wav");
    QCOMPARE(entry.fileName(), "test2.wav");

    entry.setParameter(OtoEntry::Alias, "test1");
    QCOMPARE(entry.alias(), "test1");
    entry.setParameter(OtoEntry::ALIAS, "test2");
    QCOMPARE(entry.alias(), "test2");

    entry.setParameter(OtoEntry::Left, 1.0);
    QCOMPARE(entry.left(), 1.0);
    entry.setParameter(OtoEntry::LEFT, 2.0);
    QCOMPARE(entry.left(), 2.0);

    entry.setParameter(OtoEntry::Consonant, 1.0);
    QCOMPARE(entry.consonant(), 1.0);
    entry.setParameter(OtoEntry::CONSONANT, 2.0);
    QCOMPARE(entry.consonant(), 2.0);

    entry.setParameter(OtoEntry::Consonant, 1.0);
    QCOMPARE(entry.consonant(), 1.0);
    entry.setParameter(OtoEntry::CONSONANT, 2.0);
    QCOMPARE(entry.consonant(), 2.0);

    entry.setParameter(OtoEntry::Right, 1.0);
    QCOMPARE(entry.right(), 1.0);
    entry.setParameter(OtoEntry::RIGHT, 2.0);
    QCOMPARE(entry.right(), 2.0);

    entry.setParameter(OtoEntry::PreUtterance, 1.0);
    QCOMPARE(entry.preUtterance(), 1.0);
    entry.setParameter(OtoEntry::PREUTTERANCE, 2.0);
    QCOMPARE(entry.preUtterance(), 2.0);

    entry.setParameter(OtoEntry::Overlap, 1.0);
    QCOMPARE(entry.overlap(), 1.0);
    entry.setParameter(OtoEntry::OVERLAP, 2.0);
    QCOMPARE(entry.overlap(), 2.0);
}

void OtoUtilTest::writeToFileTest()
{
    OtoFileReader reader(":/file2test/normalData.ini");
    auto entryList = reader.getEntryList();

    QStandardPaths::setTestModeEnabled(true);
    auto destFileName = QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation)).filePath("testSave.ini");
    QVERIFY(OtoEntryFunctions::writeOtoListToFile(destFileName, entryList));

    reader.setFileName(destFileName);
    auto entryListDest = reader.getEntryList();

    QCOMPARE(entryListDest, entryList);

    QFile::remove(destFileName);
}

QTEST_MAIN(OtoUtilTest)

#include "tst_otoutiltest.moc"
