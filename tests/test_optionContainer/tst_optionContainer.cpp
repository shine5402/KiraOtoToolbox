#include <QtTest>

#include "toolBase/OptionContainer.h"

class TestOptionContainer : public QObject
{
    Q_OBJECT
private slots:
    void testGetSetRoundTrip();
    void testGetDefaultValue();
    void testSetReplaceFlag();
    void testRemoveOption();
    void testCountAndIsEmpty();
    void testExists();
    void testClear();
    void testGetOptionKeys();
    void testEqualityOperator();
    void testCombineNoPrefix();
    void testCombineWithPrefix();
    void testStaticCombine();
    void testExtract();
    void testUnCombine();
};

void TestOptionContainer::testGetSetRoundTrip()
{
    OptionContainer opts;
    opts.setOption("stringKey", QString("hello"));
    QCOMPARE(opts.getOption("stringKey").toString(), QString("hello"));

    opts.setOption("intKey", 42);
    QCOMPARE(opts.getOption("intKey").toInt(), 42);

    opts.setOption("boolKey", true);
    QCOMPARE(opts.getOption("boolKey").toBool(), true);

    opts.setOption("doubleKey", 3.14);
    QCOMPARE(opts.getOption("doubleKey").toDouble(), 3.14);
}

void TestOptionContainer::testGetDefaultValue()
{
    OptionContainer opts;
    QCOMPARE(opts.getOption("nonexistent", QString("default")).toString(), QString("default"));
    QCOMPARE(opts.getOption("nonexistent", 99).toInt(), 99);

    bool matched = false;
    opts.getOption("exists", {}, &matched);
    QVERIFY(!matched);

    opts.setOption("exists", QString("yes"));
    opts.getOption("exists", {}, &matched);
    QVERIFY(matched);
}

void TestOptionContainer::testSetReplaceFlag()
{
    OptionContainer opts;
    bool replaced = false;
    opts.setOption("key", 1, &replaced);
    QVERIFY(!replaced);

    opts.setOption("key", 2, &replaced);
    QVERIFY(replaced);
    QCOMPARE(opts.getOption("key").toInt(), 2);
}

void TestOptionContainer::testRemoveOption()
{
    OptionContainer opts;
    opts.setOption("key", 42);
    QVERIFY(opts.exists("key"));
    QVERIFY(opts.removeOption("key"));
    QVERIFY(!opts.exists("key"));
    QVERIFY(!opts.removeOption("key"));
}

void TestOptionContainer::testCountAndIsEmpty()
{
    OptionContainer opts;
    QVERIFY(opts.isEmpty());
    QCOMPARE(opts.count(), 0);

    opts.setOption("a", 1);
    QVERIFY(!opts.isEmpty());
    QCOMPARE(opts.count(), 1);

    opts.setOption("b", 2);
    QCOMPARE(opts.count(), 2);
}

void TestOptionContainer::testExists()
{
    OptionContainer opts;
    QVERIFY(!opts.exists("key"));
    opts.setOption("key", 1);
    QVERIFY(opts.exists("key"));
}

void TestOptionContainer::testClear()
{
    OptionContainer opts;
    opts.setOption("a", 1);
    opts.setOption("b", 2);
    opts.clear();
    QVERIFY(opts.isEmpty());
    QCOMPARE(opts.count(), 0);
}

void TestOptionContainer::testGetOptionKeys()
{
    OptionContainer opts;
    opts.setOption("z", 3);
    opts.setOption("a", 1);
    auto keys = opts.getOptionKeys();
    QCOMPARE(keys.size(), 2);
    QVERIFY(keys.contains("a"));
    QVERIFY(keys.contains("z"));
}

void TestOptionContainer::testEqualityOperator()
{
    OptionContainer a, b;
    QVERIFY(a == b);

    a.setOption("key", 1);
    QVERIFY(a != b);

    b.setOption("key", 1);
    QVERIFY(a == b);

    b.setOption("key", 2);
    QVERIFY(a != b);
}

void TestOptionContainer::testCombineNoPrefix()
{
    OptionContainer a, b;
    a.setOption("x", 1);
    b.setOption("y", 2);

    a.combine(b);
    QCOMPARE(a.getOption("x").toInt(), 1);
    QCOMPARE(a.getOption("y").toInt(), 2);
    QCOMPARE(a.count(), 2);
}

void TestOptionContainer::testCombineWithPrefix()
{
    OptionContainer a, b;
    a.setOption("x", 1);
    b.setOption("y", 2);

    a.combine(b, "prefix_");
    QCOMPARE(a.getOption("x").toInt(), 1);
    QCOMPARE(a.getOption("prefix_y").toInt(), 2);
    QCOMPARE(a.count(), 2);
}

void TestOptionContainer::testStaticCombine()
{
    OptionContainer a, b;
    a.setOption("x", 1);
    b.setOption("y", 2);

    auto c = OptionContainer::combine(a, b, "ns_");
    QCOMPARE(c.getOption("x").toInt(), 1);
    QCOMPARE(c.getOption("ns_y").toInt(), 2);
    QCOMPARE(a.count(), 1); // a unchanged
}

void TestOptionContainer::testExtract()
{
    OptionContainer opts;
    opts.setOption("tool_a", 1);
    opts.setOption("tool_b", 2);
    opts.setOption("other", 3);

    auto extracted = opts.extract("tool_");
    QCOMPARE(extracted.count(), 2);
    QCOMPARE(extracted.getOption("a").toInt(), 1);
    QCOMPARE(extracted.getOption("b").toInt(), 2);

    // Original unchanged
    QCOMPARE(opts.count(), 3);
}

void TestOptionContainer::testUnCombine()
{
    OptionContainer opts;
    opts.setOption("tool_a", 1);
    opts.setOption("tool_b", 2);
    opts.setOption("other", 3);

    auto extracted = opts.unCombine("tool_");
    QCOMPARE(extracted.count(), 2);
    QCOMPARE(extracted.getOption("a").toInt(), 1);

    // Original keys removed
    QCOMPARE(opts.count(), 1);
    QVERIFY(opts.exists("other"));
    QVERIFY(!opts.exists("tool_a"));
}

QTEST_MAIN(TestOptionContainer)
#include "tst_optionContainer.moc"
