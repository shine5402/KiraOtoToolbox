#ifndef CONVERTPLUSMINUSRIGHTDIALOGADAPTER_H
#define CONVERTPLUSMINUSRIGHTDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class ConvertPlusMinusRightDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE ConvertPlusMinusRightDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Convert ±right value"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::ValueOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // CONVERTPLUSMINUSRIGHTDIALOGADAPTER_H
