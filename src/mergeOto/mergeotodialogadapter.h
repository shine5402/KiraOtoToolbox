#ifndef MERGEOTODIALOGADAPTER_H
#define MERGEOTODIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class MergeOtoDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MergeOtoDialogAdapter(QObject* parent = nullptr);
    DEFINE_TOOL_NAME("Merge oto")
};

#endif // MERGEOTODIALOGADAPTER_H
