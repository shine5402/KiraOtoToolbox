#ifndef CHAINDIALOGADAPTER_H
#define CHAINDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class ChainDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE ChainDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Perform multiple actions"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::MetaActions; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // CHAINDIALOGADAPTER_H
