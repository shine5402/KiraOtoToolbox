#include "toolmanager.h"

ToolManager::ToolManager(QObject *parent) : QObject(parent)
{

}

ToolManager* ToolManager::getManager()
{
    return manager;
}

void ToolManager::registerTool(const QString& group, const Tool& tool)
{
    tools.append(tool);
    toolGroups.insert(group, tool);
    if (!toolGroupNames.contains(group))
    {
        toolGroupNames.append(group);
    }
}

void ToolManager::registerTool(const QString& group, const Tool& tool, QString toolName)
{
    toolNameCache.insert(tool.toolAdapterMetaObj.className(), toolName);
    registerTool(group, tool);
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
    toolNameCache.remove(tool.toolAdapterMetaObj.className());
}

bool ToolManager::contains(const Tool& tool) const
{
    return tools.contains(tool);
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

QString ToolManager::getToolName(const Tool& tool) const
{
    return toolNameCache.value(tool.toolAdapterMetaObj.className());
}

ToolManager* ToolManager::manager = new ToolManager();

QString Tool::toolName() const {
    auto cached = ToolManager::getManager()->getToolName(*this);
    if (!cached.isEmpty()){
        return cached;
    }
    if (auto adapter = std::unique_ptr<ToolDialogAdapter>(
                qobject_cast<ToolDialogAdapter *>(
                    toolAdapterMetaObj.newInstance()))){
        return adapter->getToolName();
    }
    return {};
}
