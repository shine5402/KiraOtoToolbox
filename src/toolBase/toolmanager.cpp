#include "toolmanager.h"

ToolManager::ToolManager(QObject *parent) : QObject(parent)
{

}

ToolManager* ToolManager::getManager()
{
    return manager;
}

void ToolManager::registerTool(const QString& group, ToolDialogAdapter* dialogAdapter, OtoListModifyWorker* modifyWorker, ToolOptionWidget* optionWidget, QString name)
{
    Tool tool{dialogAdapter, modifyWorker, optionWidget, name};
    registerTool(group, tool);
}

void ToolManager::registerTool(const QString& group, const Tool& tool)
{
    if (!tool.getDialogAdapter())
        tool.getModifyWorker()->setParent(this);
    else
        tool.getDialogAdapter()->setParent(this);
    tools.append(tool);
    toolGroups.insert(group, tool);
    if (!toolGroupNames.contains(group))
    {
        toolGroupNames.append(group);
    }
}

void ToolManager::unRegisterTool(int i)
{
    auto tool = tools.at(i);
    unRegisterTool(tool);
}

void ToolManager::unRegisterTool(const Tool& tool)
{
    auto group = toolGroups.key(tool);
    toolGroups.remove(group, tool);
    tools.removeOne(tool);
    if (!toolGroups.contains(group))
        toolGroupNames.removeOne(group);
}

QVector<Tool> ToolManager::getTools() const
{
    return tools;
}

QMultiHash<QString, Tool> ToolManager::getToolGroups() const
{
    return toolGroups;
}

QStringList ToolManager::getToolGroupNamesInRegisterOrder() const
{
    return toolGroupNames;
}

ToolManager* ToolManager::manager = new ToolManager();


Tool::Tool(QPointer<ToolDialogAdapter> dialogAdapter, QPointer<OtoListModifyWorker> modifyWorker, QPointer<ToolOptionWidget> optionWidget, const QString& name)
    : modifyWorker(modifyWorker), dialogAdapter(dialogAdapter), optionWidget(optionWidget), name((name)) {
    if (dialogAdapter){
        if (name.isEmpty())
        {
            if (!dialogAdapter->getToolName().isEmpty())
                this->name = dialogAdapter->getToolName();
            else {
                this->name = modifyWorker->metaObject()->className();
            }
        }
        if (!modifyWorker){
            this->modifyWorker = dialogAdapter->worker;
            Q_ASSERT(this->modifyWorker);
        }
        if (!optionWidget)
        {
            this->optionWidget = dialogAdapter->optionWidget;
            Q_ASSERT(this->optionWidget);
        }
    }
}


Tool Tool::makeNewInstance(QObject* parent, QWidget* optionWidgetParent, const QString& nameModifier) const{
    OtoListModifyWorker* modifyWorkerNew = nullptr;
    ToolDialogAdapter* dialogAdapterNew = nullptr;
    ToolOptionWidget* optionWidgetNew = nullptr;

    if (dialogAdapter)
        dialogAdapterNew = qobject_cast<ToolDialogAdapter*>(dialogAdapter->metaObject()->newInstance(Q_ARG(QObject*, parent)));
    else
    {
        if (modifyWorker)
            modifyWorkerNew = qobject_cast<OtoListModifyWorker*>(modifyWorker->metaObject()->newInstance(Q_ARG(QObject*, parent)));
        if (optionWidget)
            optionWidgetNew = qobject_cast<ToolOptionWidget*>(optionWidget->metaObject()->newInstance(Q_ARG(QWidget*, optionWidgetParent)));
    }
    return Tool{dialogAdapterNew, modifyWorkerNew, optionWidgetNew, nameModifier.arg(name)};
}
