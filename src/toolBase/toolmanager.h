#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H

#include <QObject>
#include "toolBase/tooldialogadapter.h"
#include "toolBase/otolistmodifyworker.h"
#include <QPointer>

class Tool{
public:
    Tool() = default;
    Tool(QPointer<ToolDialogAdapter> dialogAdapter, QPointer<OtoListModifyWorker> modifyWorker = nullptr,
         QPointer<ToolOptionWidget> optionWidget = nullptr, const QString& name = nullptr);

    Tool(const Tool& other){
        modifyWorker = other.modifyWorker;
        dialogAdapter = other.dialogAdapter;
        name = other.name;
        optionWidget = other.optionWidget;
    }
    ~Tool(){}
    bool operator==(const Tool& rhs) const{
        return modifyWorker == rhs.modifyWorker &&
                dialogAdapter == rhs.dialogAdapter &&
                name == rhs.name &&
                optionWidget == rhs.optionWidget;
    }
    bool operator!=(const Tool& rhs) const{
        return !(*this == rhs);
    }
    void operator=(const Tool& rhs){
        if (*this != rhs){
            modifyWorker = rhs.modifyWorker;
            dialogAdapter = rhs.dialogAdapter;
            name = rhs.name;
            optionWidget = rhs.optionWidget;
        }
    }

    QPointer<OtoListModifyWorker> getModifyWorker() const{
        return modifyWorker;
    }

    QPointer<ToolDialogAdapter> getDialogAdapter() const{
        return dialogAdapter;
    }

    QString getName() const{
        return name;
    }

    QPointer<ToolOptionWidget> getOptionWidget() const{
        return optionWidget;
    }
    Tool makeNewInstance(QObject* parent = nullptr, QWidget* optionWidgetParent = nullptr, const QString& nameModifier = {"%1"}) const;
private:
    QPointer<OtoListModifyWorker> modifyWorker;
    QPointer<ToolDialogAdapter> dialogAdapter;
    QPointer<ToolOptionWidget> optionWidget;
    QString name;
};

Q_DECLARE_METATYPE(Tool)

class ToolManager : public QObject
{
    Q_OBJECT
    explicit ToolManager(QObject *parent = nullptr);
public:
    static ToolManager* getManager();

    void registerTool( const QString& group, ToolDialogAdapter* dialogAdapter, OtoListModifyWorker* modifyWorker = nullptr, ToolOptionWidget* optionWidget = nullptr,
                      QString name = {});
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
