#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class OverlapSetTest : public QObject
{
    Q_OBJECT

public:
    OverlapSetTest();
    ~OverlapSetTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

OverlapSetTest::OverlapSetTest()
{

}

OverlapSetTest::~OverlapSetTest()
{

}

void OverlapSetTest::initTestCase()
{

}

void OverlapSetTest::cleanupTestCase()
{

}

void OverlapSetTest::test_case1()
{

}

QTEST_MAIN(OverlapSetTest)

#include "tst_overlapsettest.moc"
