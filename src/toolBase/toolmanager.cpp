#include "toolmanager.h"

ToolManager::ToolManager(QObject *parent) : QObject(parent)
{

}

ToolManager* ToolManager::getManager()
{
    return manager;
}

void ToolManager::registerTool(ToolDialogAdapter* dialogAdapter, OtoListModifyWorker* modifyWorker, QString name)
{
    if (name.isEmpty())
    {
        if (!dialogAdapter->getWindowTitle().isEmpty())
            name = dialogAdapter->getWindowTitle();
        else {
            name = modifyWorker->metaObject()->className();
        }
    }
    if (!modifyWorker){
        modifyWorker = dialogAdapter->worker;
        Q_ASSERT(modifyWorker);
    }
    //dialogAdapter->findChildren<ToolOptionWidget *>().last();
    tools.append(Tool{modifyWorker, dialogAdapter, name});
}

void ToolManager::registerTool(const Tool& tool)
{
    tool.getModifyWorker()->setParent(this);
    tool.getDialogAdapter()->setParent(this);
    tools.append(tool);
}

void ToolManager::unRegisterTool(int i)
{
    tools.removeAt(i);
}

void ToolManager::unRegisterTool(const Tool& tool)
{
    tools.removeOne(tool);
}

QVector<Tool> ToolManager::getTools() const
{
    return tools;
}

ToolManager::Garbo ToolManager::garbo{};
ToolManager* ToolManager::manager = new ToolManager();

ToolManager::Garbo::~Garbo()
{
    manager->deleteLater();
}
