#ifndef OVERLAPBATCHSETDIALOGADAPTER_H
#define OVERLAPBATCHSETDIALOGADAPTER_H

#include <QWidget>
#include "toolBase/tooldialogadapter.h"


class OverlapBatchSetDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit OverlapBatchSetDialogAdapter(QObject *parent = nullptr);
    DEFINE_TOOL_NAME("Set overlap in batch")
};

#endif // OVERLAPBATCHSETDIALOGADAPTER_H
