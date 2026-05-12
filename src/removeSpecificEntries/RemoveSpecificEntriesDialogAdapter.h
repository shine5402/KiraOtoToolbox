#ifndef REMOVESPECIFICENTRIESDIALOGADAPTER_H
#define REMOVESPECIFICENTRIESDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class RemoveSpecificEntriesDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit RemoveSpecificEntriesDialogAdapter(QObject *parent);
    Q_INVOKABLE static QString toolName() { return tr("Remove specific entries"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::EntryOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // REMOVESPECIFICENTRIESDIALOGADAPTER_H
