#include <QtTest>
#include <QCoreApplication>
#include <QAbstractItemModelTester>
#include "utils/models/otolistmodel.h"
#include "utils/models/otolistshowvaluechangemodel.h"

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
private slots:
    void otoListModel_modelTesterTest();
    void otoListModel_dataFetchTest();

    void otoListShowValueChangeModel_modelTesterTest();
    void otoListShowValueChangeModel_dataFetchTest();
    void otoListShowValueChangeModel_dataFetchTest_data();
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

        OtoListShowValueChangeModel* model = new OtoListShowValueChangeModel(&normalList, &changedList, changedParameter, this);

        for (int i = 0; i < normalList.count(); ++i){
            int offset = 0;
            for (int j = 0; j < 7 + changedParameterCount; ++j){
                auto index = model->index(i,j);
                auto expected = [&]() -> QVariant{
                        static bool returnChanged = false;
                        static OtoEntry::OtoParameter returnChangedWhich;
                        if (returnChanged){
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
                qDebug("i = %d, j = %d", i, j);
                auto actual = model->data(index);
                QCOMPARE(actual, expected);
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

void UtilModelsTest::otoListShowValueChangeModel_dataFetchTest_data()
{

    QTest::addColumn<OtoEntry::OtoParameters>("changedParameter");
    QTest::addColumn<int>("changedParameterCount");
    QTest::addColumn<OtoEntryList>("changedList");


    QTest::addRow("FileName") << OtoEntry::OtoParameters(OtoEntry::FileName) << 1 <<
                                 OtoEntryList{OtoEntry{"_さんささすぃさすさ1.wav=- さ,1,2,3,4,5"}, OtoEntry{" _さんささすぃさすさ.wav=a さ,1,2,3,4,5"},
                                 OtoEntry{"_さんささすぃさすさ.wav=a さ2,1,2,3,4,5"}};

    QTest::addRow("Alias") << OtoEntry::OtoParameters(OtoEntry::Alias) << 1 << OtoEntryList{
                              OtoEntry{"_さんささすぃさすさ.wav=- さ1,1,2,3,4,5"}, OtoEntry{" _さんささすぃさすさ.wav=a さ1,1,2,3,4,5"},
                              OtoEntry{"_さんささすぃさすさ.wav=a さ3,1,2,3,4,5"}};
    QTest::addRow("FileName & Alias") << OtoEntry::OtoParameters(OtoEntry::FileName | OtoEntry::Alias) << 2 <<
                                         OtoEntryList{OtoEntry{"_さんささすぃさすさ1.wav=- さ,2,2,3,4,5"}, OtoEntry{" _さんささすぃさすさ.wav=a さ,3,2,3,4,5"},
                                         OtoEntry{"_さんささすぃさすさ.wav=a さ2,2,2,3,4,5"}};

}

QTEST_MAIN(UtilModelsTest)

#include "tst_utilmodelstest.moc"
