#ifndef CONVERTPLUSMINUSRIGHTDIALOGADAPTER_H
#define CONVERTPLUSMINUSRIGHTDIALOGADAPTER_H

#include "toolBase/ToolDialogAdapter.h"

class ConvertPlusMinusRightDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE ConvertPlusMinusRightDialogAdapter(QObject *parent = nullptr);
    DEFINE_TOOL_NAME("Convert ±right value")
};

#endif // CONVERTPLUSMINUSRIGHTDIALOGADAPTER_H
