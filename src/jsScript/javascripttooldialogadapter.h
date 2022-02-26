#ifndef JAVASCRIPTTOOLDIALOGADAPTER_H
#define JAVASCRIPTTOOLDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class JavaScriptToolDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit JavaScriptToolDialogAdapter(QObject *parent = nullptr);
    DEFINE_TOOL_NAME("Javascript scripting")
};

#endif // JAVASCRIPTTOOLDIALOGADAPTER_H
