#ifndef TEMPOTRANSFORMDIALOGADAPTER_H
#define TEMPOTRANSFORMDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class TempoTransformDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TempoTransformDialogAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Tempo transfrom for template"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::ValueOperations; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // TEMPOTRANSFORMDIALOGADAPTER_H
