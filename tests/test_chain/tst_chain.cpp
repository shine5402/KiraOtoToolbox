#include <QtTest>

#include "chain/ChainElement.h"
#include "chain/ChainOtoListModifyWorker.h"
#include "notDoAnything/NotDoAnythingDialogAdapter.h"
#include "toolBase/ToolManager.h"
#include "OtoTestUtils.h"

class TestChain : public QObject
{
    Q_OBJECT
private slots:
    void testSingleStep();
    void testTwoSteps();
    void testEmptySteps_identity();
    void testEmptyInput();
};

void TestChain::testSingleStep()
{
    ChainOtoListModifyWorker worker;
    auto src = makeCvVoicebank();

    QVector<ChainElement> steps;
    ChainElement step;
    step.tool = Tool(NotDoAnythingDialogAdapter::staticMetaObject);
    step.options = OptionContainer{};
    steps.append(step);

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"steps", QVariant::fromValue(steps)},
        {"load/fileName", "/tmp/dummy.ini"},
    });
    worker.doWork(src, result, secondSave, opts);

    // NotDoAnything passes through unchanged
    QCOMPARE(result.size(), src.size());
    for (int i = 0; i < src.size(); ++i)
        QVERIFY(result.at(i) == src.at(i));
}

void TestChain::testTwoSteps()
{
    ChainOtoListModifyWorker worker;
    auto src = makeCvVoicebank();

    QVector<ChainElement> steps;
    for (int i = 0; i < 2; ++i) {
        ChainElement step;
        step.tool = Tool(NotDoAnythingDialogAdapter::staticMetaObject);
        step.options = OptionContainer{};
        steps.append(step);
    }

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"steps", QVariant::fromValue(steps)},
        {"load/fileName", "/tmp/dummy.ini"},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
}

void TestChain::testEmptySteps_identity()
{
    ChainOtoListModifyWorker worker;
    auto src = makeCvVoicebank();

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"steps", QVariant::fromValue(QVector<ChainElement>{})},
        {"load/fileName", "/tmp/dummy.ini"},
    });
    worker.doWork(src, result, secondSave, opts);

    QCOMPARE(result.size(), src.size());
    for (int i = 0; i < src.size(); ++i)
        QVERIFY(result.at(i) == src.at(i));
}

void TestChain::testEmptyInput()
{
    ChainOtoListModifyWorker worker;

    QVector<ChainElement> steps;
    ChainElement step;
    step.tool = Tool(NotDoAnythingDialogAdapter::staticMetaObject);
    step.options = OptionContainer{};
    steps.append(step);

    OtoEntryList result, secondSave;
    auto opts = makeOptions({
        {"steps", QVariant::fromValue(steps)},
        {"load/fileName", "/tmp/dummy.ini"},
    });
    worker.doWork({}, result, secondSave, opts);
    QVERIFY(result.isEmpty());
}

QTEST_MAIN(TestChain)
#include "tst_chain.moc"
