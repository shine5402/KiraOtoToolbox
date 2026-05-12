#ifndef REMOVEDUPLICATEDIALOGADAPTER_H
#define REMOVEDUPLICATEDIALOGADAPTER_H

#include <QWidget>

#include "toolBase/ToolDialogAdapter.h"

class RemoveDuplicateDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit RemoveDuplicateDialogAdapter(QObject *parent = nullptr);
    void replaceUIWidgets(QLayout *rootLayout) override;
    Q_INVOKABLE static QString toolName() { return tr("Remove and organize duplicated entries"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::EntryOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // REMOVEDUPLICATEDIALOGADAPTER_H
