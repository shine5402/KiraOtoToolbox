#include "ToolManager.h"

ToolManager::ToolManager(QObject *parent) : QObject(parent)
{
}

ToolManager *ToolManager::getManager()
{
    return manager;
}

void ToolManager::registerTool(ToolCategory category, const Tool &tool)
{
    tools.append(tool);
    toolGroups[category].append(tool);
    if (!toolGroupNames.contains(category)) {
        toolGroupNames.append(category);
    }
}

void ToolManager::unRegisterTool(int i)
{
    auto tool = tools.at(i);
    unRegisterTool(tool);
}

void ToolManager::unRegisterTool(const Tool &tool)
{
    for (auto it = toolGroups.begin(); it != toolGroups.end(); ++it) {
        auto &vec = it.value();
        if (vec.removeOne(tool)) {
            if (vec.isEmpty()) {
                toolGroups.remove(it.key());
                toolGroupNames.removeOne(it.key());
            }
            break;
        }
    }
    tools.removeOne(tool);
}

QVector<Tool> ToolManager::getTools() const
{
    return tools;
}

QHash<ToolCategory, QVector<Tool>> ToolManager::getToolGroups() const
{
    return toolGroups;
}

QVector<ToolCategory> ToolManager::getToolGroupNamesInRegisterOrder() const
{
    return toolGroupNames;
}

ToolManager *ToolManager::manager = new ToolManager();
