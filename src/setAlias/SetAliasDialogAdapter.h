#ifndef SETALIASDIALOGADAPTER_H
#define SETALIASDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class SetAliasDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE SetAliasDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Set alias"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::AliasOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // SETALIASDIALOGADAPTER_H
