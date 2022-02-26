#ifndef PRECENTEREDCHANGEVALUEADAPTER_H
#define PRECENTEREDCHANGEVALUEADAPTER_H

#include <toolBase/tooldialogadapter.h>

class PreCenteredChangeValueAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit PreCenteredChangeValueAdapter(QObject *parent = nullptr);
    DEFINE_TOOL_NAME("Pre-centered change value")
};

#endif // PRECENTEREDCHANGEVALUEADAPTER_H
