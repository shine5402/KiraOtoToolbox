#include <QtTest>

// add necessary includes here

class UtilWidgetsTest : public QObject
{
    Q_OBJECT

public:
    UtilWidgetsTest();
    ~UtilWidgetsTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

UtilWidgetsTest::UtilWidgetsTest()
{

}

UtilWidgetsTest::~UtilWidgetsTest()
{

}

void UtilWidgetsTest::initTestCase()
{

}

void UtilWidgetsTest::cleanupTestCase()
{

}

void UtilWidgetsTest::test_case1()
{

}

QTEST_MAIN(UtilWidgetsTest)

#include "tst_utilwidgetstest.moc"
