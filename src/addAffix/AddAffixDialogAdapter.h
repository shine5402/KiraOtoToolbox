#ifndef ADDAFFIXDIALOGADAPTER_H
#define ADDAFFIXDIALOGADAPTER_H

#include "../toolBase/ToolDialogAdapter.h"

class AddAffixDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE AddAffixDialogAdapter(QObject *parent = nullptr);
    DEFINE_TOOL_NAME("Add affix (prefix/suffix)")
};

#endif // ADDAFFIXDIALOGADAPTER_H
