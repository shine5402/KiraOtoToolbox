#ifndef TRIMAROUNDSPECIFICVALUEDIALOGADAPTER_H
#define TRIMAROUNDSPECIFICVALUEDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class TrimAroundSpecificValueDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE TrimAroundSpecificValueDialogAdapter(QObject* parent = nullptr);
    DEFINE_TOOL_NAME("Trim around specific value")
};

#endif // TRIMAROUNDSPECIFICVALUEDIALOGADAPTER_H
