#ifndef REMOVEBLANKDIALOGADAPTER_H
#define REMOVEBLANKDIALOGADAPTER_H

#include <toolBase/ToolDialogAdapter.h>

class RemoveBlankDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE RemoveBlankDialogAdapter(QObject* parent = nullptr);
    DEFINE_TOOL_NAME("Remove empty entries")
};

#endif // REMOVEBLANKDIALOGADAPTER_H
