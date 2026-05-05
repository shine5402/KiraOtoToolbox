#ifndef NOTDOANYTHINGDIALOGADAPTER_H
#define NOTDOANYTHINGDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class NotDoAnythingDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit NotDoAnythingDialogAdapter(QObject *parent = nullptr);
    DEFINE_TOOL_NAME("Adjust decimal precision")
};

#endif // NOTDOANYTHINGDIALOGADAPTER_H
