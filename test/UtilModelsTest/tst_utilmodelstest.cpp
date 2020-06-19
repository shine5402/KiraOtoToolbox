#include <QtTest>
#include <QCoreApplication>
#include <QAbstractItemModelTester>
#include "utils/models/otolistmodel.h"

// add necessary includes here

class UtilModelsTest : public QObject
{
    Q_OBJECT

public:
    UtilModelsTest();
    ~UtilModelsTest();
private:
    enum {fileName, alias, left, consonant, right, preUtterance, overlap};
    OtoEntryList list{OtoEntry{"_さんささすぃさすさ.wav=- さ,1,2,3,4,5"}, OtoEntry{" _さんささすぃさすさ.wav=a さ,1,2,3,4,5"}, OtoEntry{"_さんささすぃさすさ.wav=a さ2,1,2,3,4,5"}};
    OtoListModel* model = new OtoListModel(&list);
private slots:
    void modelTesterTest();
    void dataFetchTest();


};

UtilModelsTest::UtilModelsTest()
{

}

UtilModelsTest::~UtilModelsTest()
{
    model->deleteLater();
}

void UtilModelsTest::modelTesterTest()
{
    OtoEntryList list {OtoEntry {"_さんささすぃさすさ.wav=- さ,1,2,3,4,5"},
                      OtoEntry{" _さんささすぃさすさ.wav=a さ,1,2,3,4,5"},
                      OtoEntry{"_さんささすぃさすさ.wav=a さ2,1,2,3,4,5"}};
    OtoListModel* model = new OtoListModel(&list);
    auto tester = new QAbstractItemModelTester(model);

    tester->deleteLater();
}

void UtilModelsTest::dataFetchTest()
{
    for (int i = 0; i < list.count(); ++i){
        for (int j = 0; j < 7; ++j){
            auto index = model->index(i,j);
            auto expected = [&]() -> QVariant{
                    switch (j) {
                    case fileName: return list.at(i).fileName();
                    case alias: return list.at(i).alias();
                    case left: return list.at(i).left();
                    case consonant: return list.at(i).consonant();
                    case right: return list.at(i).right();
                    case preUtterance: return list.at(i).preUtterance();
                    case overlap: return list.at(i).overlap();
        }
                    return {};
        }();
            auto actual = model->data(index);
            QCOMPARE(actual, expected);
        }
    }
}

QTEST_MAIN(UtilModelsTest)

#include "tst_utilmodelstest.moc"
