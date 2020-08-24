#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H

#include <QObject>
#include "toolBase/tooldialogadapter.h"
#include "toolBase/otolistmodifyworker.h"

class Tool{
public:
    Tool(ToolDialogAdapter* dialogAdapter, OtoListModifyWorker* modifyWorker = nullptr,
         ToolOptionWidget* optionWidget = nullptr, const QString& name = nullptr);

    Tool(const Tool& other){
        modifyWorker = other.modifyWorker;
        dialogAdapter = other.dialogAdapter;
        name = other.name;
        optionWidget = other.optionWidget;
    }
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

    OtoListModifyWorker* getModifyWorker() const{
        return modifyWorker;
    }

    ToolDialogAdapter* getDialogAdapter() const{
        return dialogAdapter;
    }

    QString getName() const{
        return name;
    }

    ToolOptionWidget* getOptionWidget() const{
        return optionWidget;
    }

private:
    OtoListModifyWorker* modifyWorker;
    ToolDialogAdapter* dialogAdapter;
    ToolOptionWidget* optionWidget;
    QString name;
};


class ToolManager : public QObject
{
    Q_OBJECT
    explicit ToolManager(QObject *parent = nullptr);
public:
    static ToolManager* getManager();

    void registerTool(ToolDialogAdapter* dialogAdapter, OtoListModifyWorker* modifyWorker = nullptr, ToolOptionWidget* optionWidget = nullptr, QString name = {});
    void registerTool(const Tool& tool);
    void unRegisterTool(int i);
    void unRegisterTool(const Tool& tool);

    QVector<Tool> getTools() const;

private:
    static ToolManager* manager;
    static class Garbo{
    public:
        ~Garbo();
    } garbo;

    QVector<Tool> tools;
};

#endif // TOOLMANAGER_H
