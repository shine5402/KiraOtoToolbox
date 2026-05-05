#include <QtTest>

#include "addAffix/AddAffixDialogAdapter.h"
#include "notDoAnything/NotDoAnythingDialogAdapter.h"
#include "removeBlank/RemoveBlankDialogAdapter.h"
#include "toolBase/ToolManager.h"

class TestToolManager : public QObject
{
    Q_OBJECT
private slots:
    void testRegisterAndCount();
    void testGetToolGroups();
    void testGetToolGroupNamesInRegisterOrder();
    void testUnregisterByIndex();
    void testUnregisterByTool();
    void testToolName();
    void testGetWorkerInstance();
    void testAdapterGetWorkerInstance();
    void testGetOptionWidgetInstance();
    void testDuplicateRegistration();
};

void TestToolManager::testRegisterAndCount()
{
    auto *mgr = ToolManager::getManager();
    // Start fresh — clear any previously registered tools
    while (mgr->getTools().count() > 0)
        mgr->unRegisterTool(0);

    mgr->registerTool("Entry operations", Tool(RemoveBlankDialogAdapter::staticMetaObject));
    mgr->registerTool("Alias operations", Tool(AddAffixDialogAdapter::staticMetaObject));
    mgr->registerTool("Meta actions", Tool(NotDoAnythingDialogAdapter::staticMetaObject));

    QCOMPARE(mgr->getTools().count(), 3);
}

void TestToolManager::testGetToolGroups()
{
    auto *mgr = ToolManager::getManager();
    auto groups = mgr->getToolGroups();

    QCOMPARE(groups.size(), 3);
    QCOMPARE(groups.values("Entry operations").size(), 1);
    QCOMPARE(groups.values("Alias operations").size(), 1);
    QCOMPARE(groups.values("Meta actions").size(), 1);
}

void TestToolManager::testGetToolGroupNamesInRegisterOrder()
{
    auto *mgr = ToolManager::getManager();
    auto names = mgr->getToolGroupNamesInRegisterOrder();

    QCOMPARE(names.size(), 3);
    QCOMPARE(names.at(0), QString("Entry operations"));
    QCOMPARE(names.at(1), QString("Alias operations"));
    QCOMPARE(names.at(2), QString("Meta actions"));
}

void TestToolManager::testUnregisterByIndex()
{
    auto *mgr = ToolManager::getManager();
    int count = mgr->getTools().count();

    mgr->unRegisterTool(0);
    QCOMPARE(mgr->getTools().count(), count - 1);
}

void TestToolManager::testUnregisterByTool()
{
    auto *mgr = ToolManager::getManager();
    int count = mgr->getTools().count();
    QVERIFY(count > 0);

    auto tool = mgr->getTools().first();
    mgr->unRegisterTool(tool);
    QCOMPARE(mgr->getTools().count(), count - 1);
}

void TestToolManager::testToolName()
{
    auto *mgr = ToolManager::getManager();
    // Re-register for clean state
    while (mgr->getTools().count() > 0)
        mgr->unRegisterTool(0);

    mgr->registerTool("Test", Tool(NotDoAnythingDialogAdapter::staticMetaObject));
    QCOMPARE(mgr->getTools().first().toolName(), QString("Adjust decimal precision"));
}

void TestToolManager::testGetWorkerInstance()
{
    Tool tool(NotDoAnythingDialogAdapter::staticMetaObject);
    auto worker = tool.getWorkerInstance();
    QVERIFY(worker != nullptr);
}

void TestToolManager::testAdapterGetWorkerInstance()
{
    // This path calls ToolDialogAdapter::getWorkerInstance() which internally
    // calls QMetaObject::newInstance() — the exact code path that regressed
    // when Qt 6.5+ changed newInstance to a template that deduces argument types.
    QList<QMetaObject> adapters = {
        NotDoAnythingDialogAdapter::staticMetaObject,
        AddAffixDialogAdapter::staticMetaObject,
        RemoveBlankDialogAdapter::staticMetaObject,
    };
    for (const auto &adapterMeta : adapters) {
        auto adapter = qobject_cast<ToolDialogAdapter *>(adapterMeta.newInstance(Q_ARG(QObject *, nullptr)));
        QVERIFY2(adapter, "Failed to create adapter instance");
        auto worker = adapter->getWorkerInstance();
        QVERIFY2(worker, "getWorkerInstance() returned null — newInstance() argument type may not match constructor");
        delete adapter;
    }
}

void TestToolManager::testGetOptionWidgetInstance()
{
    Tool tool(NotDoAnythingDialogAdapter::staticMetaObject);
    auto widget = tool.getToolOptionWidgetInstance(nullptr);
    QVERIFY(widget != nullptr);
    delete widget;
}

void TestToolManager::testDuplicateRegistration()
{
    auto *mgr = ToolManager::getManager();
    while (mgr->getTools().count() > 0)
        mgr->unRegisterTool(0);

    Tool tool(NotDoAnythingDialogAdapter::staticMetaObject);
    mgr->registerTool("Test", tool);
    mgr->registerTool("Test", tool);

    // Same tool registered twice
    QCOMPARE(mgr->getTools().count(), 2);
    QCOMPARE(mgr->getToolGroups().values("Test").size(), 2);
}

QTEST_MAIN(TestToolManager)
#include "tst_toolManager.moc"
