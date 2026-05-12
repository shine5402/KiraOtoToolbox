#ifndef NOTDOANYTHINGDIALOGADAPTER_H
#define NOTDOANYTHINGDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class NotDoAnythingDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit NotDoAnythingDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Adjust decimal precision"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::MetaActions; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // NOTDOANYTHINGDIALOGADAPTER_H
