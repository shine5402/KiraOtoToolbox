#ifndef MERGEOTODIALOGADAPTER_H
#define MERGEOTODIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class MergeOtoDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MergeOtoDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Merge oto"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::EntryOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // MERGEOTODIALOGADAPTER_H
