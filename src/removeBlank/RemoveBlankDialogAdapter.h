#ifndef REMOVEBLANKDIALOGADAPTER_H
#define REMOVEBLANKDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class RemoveBlankDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE RemoveBlankDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Remove empty entries"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::EntryOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // REMOVEBLANKDIALOGADAPTER_H
