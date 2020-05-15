#include <QtTest>

#include <otoentry.h>
#include "../../src/removeduplicatedialog.h"

class RemoveDuplicateTest : public QObject
{
    Q_OBJECT

public:
    RemoveDuplicateTest();
    ~RemoveDuplicateTest();

private slots:
    void test_case1();

};

RemoveDuplicateTest::RemoveDuplicateTest()
{

}

RemoveDuplicateTest::~RemoveDuplicateTest()
{

}

void RemoveDuplicateTest::test_case1()
{

}

QTEST_APPLESS_MAIN(RemoveDuplicateTest)

#include "tst_removeduplicatetest.moc"
