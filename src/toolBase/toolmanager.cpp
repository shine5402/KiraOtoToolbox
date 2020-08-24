#include "toolmanager.h"

ToolManager::ToolManager(QObject *parent) : QObject(parent)
{

}

ToolManager* ToolManager::getManager()
{
    return manager;
}

void ToolManager::registerTool(ToolDialogAdapter* dialogAdapter, OtoListModifyWorker* modifyWorker, ToolOptionWidget* optionWidget, QString name)
{
    tools.append(Tool{dialogAdapter, modifyWorker, optionWidget, name});
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

Tool::Tool(ToolDialogAdapter* dialogAdapter, OtoListModifyWorker* modifyWorker, ToolOptionWidget* optionWidget, const QString& name)
    : modifyWorker(modifyWorker), dialogAdapter(dialogAdapter), optionWidget(optionWidget), name((name)) {
    if (dialogAdapter){
        if (name.isEmpty())
        {
            if (!dialogAdapter->getWindowTitle().isEmpty())
                this->name = dialogAdapter->getWindowTitle();
            else {
                this->name = modifyWorker->metaObject()->className();
            }
        }
        if (!modifyWorker){
            this->modifyWorker = dialogAdapter->worker;
            Q_ASSERT(modifyWorker);
        }
        if (!optionWidget)
        {
            this->optionWidget = dialogAdapter->optionWidget;
            Q_ASSERT(optionWidget);
        }
    }
}
