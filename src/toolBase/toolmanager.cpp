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
