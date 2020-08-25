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

ToolManager* ToolManager::manager = new ToolManager();


Tool::Tool(QPointer<ToolDialogAdapter> dialogAdapter, QPointer<OtoListModifyWorker> modifyWorker, QPointer<ToolOptionWidget> optionWidget, const QString& name)
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
