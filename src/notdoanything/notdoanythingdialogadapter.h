#ifndef NOTDOANYTHINGDIALOGADAPTER_H
#define NOTDOANYTHINGDIALOGADAPTER_H

#include "toolBase/tooldialogadapter.h"

class NotDoAnythingDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit NotDoAnythingDialogAdapter(QObject *parent = nullptr);
    DEFINE_TOOL_NAME("什么都不做")
};

#endif // NOTDOANYTHINGDIALOGADAPTER_H
