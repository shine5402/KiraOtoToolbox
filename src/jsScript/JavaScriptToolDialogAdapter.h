#ifndef JAVASCRIPTTOOLDIALOGADAPTER_H
#define JAVASCRIPTTOOLDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class JavaScriptToolDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit JavaScriptToolDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Javascript scripting"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::MetaActions; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // JAVASCRIPTTOOLDIALOGADAPTER_H
