#ifndef ADDAFFIXDIALOGADAPTER_H
#define ADDAFFIXDIALOGADAPTER_H

#include "../toolBase/ToolDialogAdapter.h"

class AddAffixDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE AddAffixDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Add affix (prefix/suffix)"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::AliasOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // ADDAFFIXDIALOGADAPTER_H
