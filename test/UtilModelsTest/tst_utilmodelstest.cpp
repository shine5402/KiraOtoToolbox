#include <QtTest>
#include <QCoreApplication>
#include <QAbstractItemModelTester>
#include "utils/models/otolistmodel.h"
#include "utils/models/otolistshowvaluechangemodel.h"
#include <cmath>

Q_DECLARE_METATYPE(QFlags<OtoEntry::OtoParameter>);
Q_DECLARE_METATYPE(OtoEntryList);

class UtilModelsTest : public QObject
{
    Q_OBJECT

public:
    UtilModelsTest();
    ~UtilModelsTest();
private:
    enum {fileName, alias, left, consonant, right, preUtterance, overlap};
    OtoEntryList normalList{OtoEntry{"_さんささすぃさすさ.wav=- さ,1,2,3,4,5"}, OtoEntry{" _さんささすぃさすさ.wav=a さ,1,2,3,4,5"}, OtoEntry{"_さんささすぃさすさ.wav=a さ2,1,2,3,4,5"}};
    OtoListModel* listModel = new OtoListModel(&normalList);
    void prepareChangedData();

private slots:
    void otoListModel_modelTesterTest();
    void otoListModel_dataFetchTest();

    void otoListShowValueChangeModel_modelTesterTest();
    void otoListShowValueChangeModel_dataFetchTest();
    void otoListShowValueChangeModel_dataFetchTest_data();
    void otoListShowValueChangeModel_headerTest();
    void otoListShowValueChangeModel_headerTest_data();
};

UtilModelsTest::UtilModelsTest()
{

}

UtilModelsTest::~UtilModelsTest()
{
    listModel->deleteLater();
}

void UtilModelsTest::otoListModel_modelTesterTest()
{
    auto tester = new QAbstractItemModelTester(listModel);

    tester->deleteLater();
}

void UtilModelsTest::otoListModel_dataFetchTest()
{
    for (int i = 0; i < normalList.count(); ++i){
        for (int j = 0; j < 7; ++j){
            auto index = listModel->index(i,j);
            auto expected = [&]() -> QVariant{
                    switch (j) {
                    case fileName: return normalList.at(i).fileName();
                    case alias: return normalList.at(i).alias();
                    case left: return normalList.at(i).left();
                    case consonant: return normalList.at(i).consonant();
                    case right: return normalList.at(i).right();
                    case preUtterance: return normalList.at(i).preUtterance();
                    case overlap: return normalList.at(i).overlap();
        }
                    return {};
        }();
            auto actual = listModel->data(index);
            QCOMPARE(actual, expected);
        }
    }
}

void UtilModelsTest::otoListShowValueChangeModel_modelTesterTest()
{
    OtoEntryList changedList{OtoEntry{"_さんささすぃさすさ.wav=- さ1,1,2,3,4,5"}, OtoEntry{" _さんささすぃさすさ.wav=a さ1,1,2,3,4,5"},
                             OtoEntry{"_さんささすぃさすさ.wav=a さ3,1,2,3,4,5"}};
    OtoListShowValueChangeModel* model = new OtoListShowValueChangeModel(&normalList, &changedList, OtoEntry::Alias, this);

    auto tester = new QAbstractItemModelTester(model);

    tester->deleteLater();
}

void UtilModelsTest::otoListShowValueChangeModel_dataFetchTest()
{try {


        QFETCH(OtoEntry::OtoParameters, changedParameter);
        QFETCH(int, changedParameterCount);
        QFETCH(OtoEntryList, changedList);
        QFETCH(QList<QList<bool>>, dataChanged);

        OtoListShowValueChangeModel* model = new OtoListShowValueChangeModel(&normalList, &changedList, changedParameter, this);

        for (int i = 0; i < normalList.count(); ++i){
            int offset = 0;
            int offsetFont = 0;
            for (int j = 0; j < 7 + changedParameterCount; ++j){
                auto index = model->index(i,j);
                auto expected = [&]() -> QVariant{
                        static bool returnChanged = false;
                        static OtoEntry::OtoParameter returnChangedWhich;
                        if (returnChanged)
                {
                        returnChanged = false;
                        return changedList.at(i).getParameter(returnChangedWhich);

            }
                        auto order = static_cast<OtoEntry::OtoParameterOrder>(j - offset);
                        auto flag = OtoEntry::getParameterFlag(order);
                        if (changedParameter.testFlag(flag)){
                        returnChanged = true;
                        returnChangedWhich = flag;
                        ++offset;
            }
                        return normalList.at(i).getParameter(flag);
            }();
                auto expectedFont = [&]() -> QVariant{
                        static bool returnChanged = false;
                        QFont font{};
                        static bool returnChangedWhich = false;
                        if (returnChanged)
                {
                        returnChanged = false;
                        if (returnChangedWhich){
                        font.setBold(true);
                        returnChangedWhich = false;
            }
                        return font;

            }
                        auto order = static_cast<OtoEntry::OtoParameterOrder>(j - offsetFont);
                        auto flag = OtoEntry::getParameterFlag(order);
                        if (changedParameter.testFlag(flag)){
                        returnChanged = true;

                        if (dataChanged.at(offsetFont).at(i))
                {
                        font.setItalic(true);
                        returnChangedWhich = true;
            }
                        ++offsetFont;
            }
                        return font;
            }();
                qDebug("i = %d, j = %d", i, j);
                auto actual = model->data(index);
                auto actualFont = model->data(index, Qt::FontRole);
                if (expected.type() == QVariant::Double)
                {
                    expected.setValue(QString::number(expected.toDouble(),'f', 3));
                }
                QCOMPARE(actual, expected);
                QCOMPARE(actualFont, expectedFont);
            }

        }
    } catch (std::exception& e) {
        qDebug() << e.what();
        throw;
    }
    catch(...){
        qDebug() << "catch sth.";
        throw;
    }
}

void UtilModelsTest::prepareChangedData()
{
    QTest::addColumn<OtoEntry::OtoParameters>("changedParameter");
    QTest::addColumn<int>("changedParameterCount");
    QTest::addColumn<OtoEntryList>("changedList");
    QTest::addColumn<QStringList>("header");
    QTest::addColumn<QList<QList<bool>>>("dataChanged");


    QTest::addRow("FileName") << OtoEntry::OtoParameters(OtoEntry::FileName) << 1 <<
                                 OtoEntryList{OtoEntry{"_さんささすぃさすさ1.wav=- さ,1,2,3,4,5"}, OtoEntry{" _さんささすぃさすさ.wav=a さ,1,2,3,4,5"},
                                 OtoEntry{"_さんささすぃさすさ.wav=a さ2,1,2,3,4,5"}}<<QStringList{
                                 "文件名",
                                 "新的文件名",
                                 "别名",
                                 "左",
                                 "固定范围",
                                 "右",
                                 "先行发声",
                                 "重叠"

} << QList<QList<bool>>{{true, false, false}, {false, false, false}, {false, false, false}};

    QTest::addRow("Alias") << OtoEntry::OtoParameters(OtoEntry::Alias) << 1 << OtoEntryList{
                              OtoEntry{"_さんささすぃさすさ.wav=- さ1,1,2,3,4,5"}, OtoEntry{" _さんささすぃさすさ.wav=a さ1,1,2,3,4,5"},
                              OtoEntry{"_さんささすぃさすさ.wav=a さ3,1,2,3,4,5"}}<<QStringList{
                              "文件名",
                              "别名",
                              "新的别名",
                              "左",
                              "固定范围",
                              "右",
                              "先行发声",
                              "重叠"

} << QList<QList<bool>>{{true, true, true}, {false, false, false}, {false, false, false}};
    QTest::addRow("FileName & Alias") << OtoEntry::OtoParameters(OtoEntry::FileName | OtoEntry::Alias) << 2 <<
                                         OtoEntryList{OtoEntry{"_さんささすぃさすさ1.wav=- さ1,1,2,3,4,5"}, OtoEntry{" _さんささすぃさすさ.wav=a さ3,1,2,3,4,5"},
                                         OtoEntry{"_さんささすぃさすさ.wav=a さ2,1,2,3,4,5"}}<<QStringList{
                                         "文件名",
                                         "新的文件名",
                                         "别名",
                                         "新的别名",
                                         "左",
                                         "固定范围",
                                         "右",
                                         "先行发声",
                                         "重叠"

} << QList<QList<bool>>{{true, false, false}, {true, true, false}, {false, false, false}};
    QTest::addRow("FileName & Alias & Left") << OtoEntry::OtoParameters(OtoEntry::FileName | OtoEntry::Alias | OtoEntry::Left) << 3 <<
                                                OtoEntryList{OtoEntry{"_さんささすぃさすさ1.wav=- さ1,2,2,3,4,5"}, OtoEntry{" _さんささすぃさすさ.wav=a さ2,3,2,3,4,5"},
                                                OtoEntry{"_さんささすぃさすさ.wav=a さ2,2,2,3,4,5"}}<<QStringList{
                                                "文件名",
                                                "新的文件名",
                                                "别名",
                                                "新的别名",
                                                "左",
                                                "新的左",
                                                "固定范围",
                                                "右",
                                                "先行发声",
                                                "重叠"

}<< QList<QList<bool>>{{true, false, false}, {true, true, false}, {true, true, true}};
}

void UtilModelsTest::otoListShowValueChangeModel_dataFetchTest_data()
{

    prepareChangedData();

}

void UtilModelsTest::otoListShowValueChangeModel_headerTest()
{
    QFETCH(OtoEntry::OtoParameters, changedParameter);
    QFETCH(int, changedParameterCount);
    QFETCH(OtoEntryList, changedList);
    QFETCH(QStringList, header);

    OtoListShowValueChangeModel* model = new OtoListShowValueChangeModel(&normalList, &changedList, changedParameter, this);
    for (int i = 0; i < 7 + changedParameterCount; ++i){
        auto actual = model->headerData(i, Qt::Horizontal);
        auto expected = header.at(i);
        QCOMPARE(actual, expected);
    }
    for (int i = 0; i < normalList.count(); ++i){
        auto actual = model->headerData(i, Qt::Vertical);
        QCOMPARE(actual, i + 1);
    }
}

void UtilModelsTest::otoListShowValueChangeModel_headerTest_data()
{
    prepareChangedData();
}

QTEST_MAIN(UtilModelsTest)

#include "tst_utilmodelstest.moc"
