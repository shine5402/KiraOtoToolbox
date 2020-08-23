#include "toolmanager.h"

ToolManager::ToolManager(QObject *parent) : QObject(parent)
{

}

ToolManager* ToolManager::getManager()
{
    return manager;
}

void ToolManager::registerTool(OtoListModifyWorker* modifyWorker, ToolDialogAdapter* dialogAdapter, QString name)
{
    if (name.isEmpty())
    {
        if (!dialogAdapter->getWindowTitle().isEmpty())
            name = dialogAdapter->getWindowTitle();
        else {
            name = modifyWorker->metaObject()->className();
        }
    }
    tools.append(Tool{modifyWorker, dialogAdapter, name});
}

void ToolManager::registerTool(const Tool& tool)
{
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
