#ifndef REPLACEFILENAMEADAPTER_H
#define REPLACEFILENAMEADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class ReplaceFileNameAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ReplaceFileNameAdapter(QObject *parent = nullptr);
    Q_INVOKABLE static QString toolName() { return tr("Replace file name (and rename file)"); }
    Q_INVOKABLE static ToolCategory toolCategory() { return ToolCategory::FilenameActions; }

    QString getToolName() const override { return toolName(); }
    ToolCategory getToolCategory() const override { return toolCategory(); }
};

#endif // REPLACEFILENAMEADAPTER_H
