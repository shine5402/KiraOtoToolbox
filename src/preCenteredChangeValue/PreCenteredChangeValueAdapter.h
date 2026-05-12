#ifndef PRECENTEREDCHANGEVALUEADAPTER_H
#define PRECENTEREDCHANGEVALUEADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class PreCenteredChangeValueAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit PreCenteredChangeValueAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Pre-centered change value"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::ValueOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // PRECENTEREDCHANGEVALUEADAPTER_H
