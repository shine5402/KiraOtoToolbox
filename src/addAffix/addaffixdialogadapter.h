#ifndef ADDAFFIXDIALOGADAPTER_H
#define ADDAFFIXDIALOGADAPTER_H

#include "../toolBase/tooldialogadapter.h"

class AddAffixDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE AddAffixDialogAdapter(QObject* parent = nullptr);
    DEFINE_TOOL_NAME("添加别名前/后缀")
};

#endif // ADDAFFIXDIALOGADAPTER_H
