#ifndef JAVASCRIPTTOOLDIALOGADAPTER_H
#define JAVASCRIPTTOOLDIALOGADAPTER_H

#include <toolBase/ToolDialogAdapter.h>

class JavaScriptToolDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit JavaScriptToolDialogAdapter(QObject *parent = nullptr);
    DEFINE_TOOL_NAME("Javascript scripting")
};

#endif // JAVASCRIPTTOOLDIALOGADAPTER_H
