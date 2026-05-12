#ifndef REMOVEAFFIXDIALOGADAPTER_H
#define REMOVEAFFIXDIALOGADAPTER_H
#include "toolBase/ToolDialogAdapter.h"

class RemoveAffixDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE RemoveAffixDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Remove prefix/suffix in alias"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::AliasOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // REMOVEAFFIXDIALOGADAPTER_H
