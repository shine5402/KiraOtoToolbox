#ifndef REMOVEAFFIXDIALOGADAPTER_H
#define REMOVEAFFIXDIALOGADAPTER_H
#include "toolBase/tooldialogadapter.h"

class RemoveAffixDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE RemoveAffixDialogAdapter(QObject* parent = nullptr);
    DEFINE_TOOL_NAME("Remove prefix/suffix in alias")
};

#endif // REMOVEAFFIXDIALOGADAPTER_H
