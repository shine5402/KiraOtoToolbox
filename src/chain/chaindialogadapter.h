#ifndef CHAINDIALOGADAPTER_H
#define CHAINDIALOGADAPTER_H

#include "toolBase/tooldialogadapter.h"

class ChainDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE ChainDialogAdapter(QObject* parent = nullptr);
    DEFINE_TOOL_NAME("进行多个操作")
};

#endif // CHAINDIALOGADAPTER_H
