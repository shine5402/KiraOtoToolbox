#ifndef TEMPOTRANSFORMDIALOGADAPTER_H
#define TEMPOTRANSFORMDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class TempoTransformDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TempoTransformDialogAdapter(QObject *parent = nullptr);
    DEFINE_TOOL_NAME("Tempo transfrom for template")
};

#endif // TEMPOTRANSFORMDIALOGADAPTER_H
