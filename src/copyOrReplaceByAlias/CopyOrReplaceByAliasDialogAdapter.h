#ifndef COPYORREPLACEBYALIASDIALOGADAPTER_H
#define COPYORREPLACEBYALIASDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class CopyOrReplaceByAliasDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit CopyOrReplaceByAliasDialogAdapter(QObject *parent);
    Q_INVOKABLE static QString toolName() { return tr("Copy/Replace by alias"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::EntryOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // COPYORREPLACEBYALIASDIALOGADAPTER_H
