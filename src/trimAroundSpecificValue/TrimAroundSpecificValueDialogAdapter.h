#ifndef TRIMAROUNDSPECIFICVALUEDIALOGADAPTER_H
#define TRIMAROUNDSPECIFICVALUEDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class TrimAroundSpecificValueDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE TrimAroundSpecificValueDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Trim around specific value"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::ValueOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // TRIMAROUNDSPECIFICVALUEDIALOGADAPTER_H
