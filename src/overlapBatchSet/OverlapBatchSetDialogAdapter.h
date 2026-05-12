#ifndef OVERLAPBATCHSETDIALOGADAPTER_H
#define OVERLAPBATCHSETDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class OverlapBatchSetDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit OverlapBatchSetDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Set overlap in batch"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::ValueOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // OVERLAPBATCHSETDIALOGADAPTER_H
