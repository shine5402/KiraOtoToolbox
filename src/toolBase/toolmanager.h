#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H

#include <QObject>
#include "toolBase/tooldialogadapter.h"
#include "toolBase/otolistmodifyworker.h"
#include <QPointer>

struct Tool{
    Tool() = default;
    Tool(QMetaObject toolAdapterMetaObj) : toolAdapterMetaObj(toolAdapterMetaObj){}

    QMetaObject toolAdapterMetaObj;

    bool operator==(const Tool& rhs) const {
        return rhs.toolName() == toolName();
    }
    bool operator!=(const Tool& rhs){
        return !(*this == rhs);
    }
    QString toolName() const {
        if (auto adapter = std::unique_ptr<ToolDialogAdapter>(
                    qobject_cast<ToolDialogAdapter *>(
                        toolAdapterMetaObj.newInstance()))){
            return adapter->getToolName();
        }
        return {};
    }

    std::unique_ptr<ToolDialogAdapter> getAdapterInstance() const{
        return std::unique_ptr<ToolDialogAdapter>(getAdapterInstance(nullptr));
    }

    ToolDialogAdapter* getAdapterInstance(QObject* parent) const{
        return qobject_cast<ToolDialogAdapter *>(
                    toolAdapterMetaObj.newInstance(Q_ARG(QObject*, parent)));
    }

    std::unique_ptr<OtoListModifyWorker> getWorkerInstance() const{
        return std::unique_ptr<OtoListModifyWorker>(getWorkerInstance(nullptr));
    }

    OtoListModifyWorker* getWorkerInstance(QObject* parent) const{
        if (auto adapter = getAdapterInstance()){
            return qobject_cast<OtoListModifyWorker *>(
                        adapter->getWorkerMetaObj().newInstance(Q_ARG(QObject*, parent)));
        }
        return {};
    }

    ToolOptionWidget* getToolOptionWidgetInstance(QWidget* parent) const{
        if (auto adapter = getAdapterInstance()){
            return qobject_cast<ToolOptionWidget *>(adapter->getOptionWidgetMetaObj().newInstance(Q_ARG(QWidget*, parent)));
        }
        return {};
    }

    QMetaObject getToolOptionWidgetMetaObj() const{
        return getAdapterInstance()->getOptionWidgetMetaObj();
    }
};

struct ToolWithOptions
{
   Tool tool;
   OptionContainer options;

   QString toolName() const{
      return tool.toolName();
   }
};

Q_DECLARE_METATYPE(Tool)
Q_DECLARE_METATYPE(ToolWithOptions)

class ToolManager : public QObject
{
    Q_OBJECT
    explicit ToolManager(QObject *parent = nullptr);
public:
    static ToolManager* getManager();

    void registerTool(const QString& group, const Tool& tool);
    void unRegisterTool(int i);
    void unRegisterTool(const Tool& tool);

    QVector<Tool> getTools() const;

    QMultiHash<QString, Tool> getToolGroups() const;

    QStringList getToolGroupNamesInRegisterOrder() const;//用来保持注册顺序

private:
    static ToolManager* manager;
    QVector<Tool> tools;
    QMultiHash<QString, Tool> toolGroups;
    QStringList toolGroupNames;
};

#endif // TOOLMANAGER_H
