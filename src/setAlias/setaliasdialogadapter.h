#ifndef SETALIASDIALOGADAPTER_H
#define SETALIASDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class SetAliasDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE SetAliasDialogAdapter(QObject *parent = nullptr);
    DEFINE_TOOL_NAME("Set alias")
};

#endif // SETALIASDIALOGADAPTER_H
