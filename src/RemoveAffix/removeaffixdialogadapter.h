#ifndef REMOVEAFFIXDIALOGADAPTER_H
#define REMOVEAFFIXDIALOGADAPTER_H
#include "toolBase/tooldialogadapter.h"

class RemoveAffixDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE RemoveAffixDialogAdapter(QObject* parent = nullptr);
    DEFINE_TOOL_NAME("去除别名前/后缀")
};

#endif // REMOVEAFFIXDIALOGADAPTER_H
