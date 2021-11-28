#ifndef REMOVESPECIFICENTRIESDIALOGADAPTER_H
#define REMOVESPECIFICENTRIESDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class RemoveSpecificEntriesDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit RemoveSpecificEntriesDialogAdapter(QObject* parent);
    DEFINE_TOOL_NAME("Remove specific entries")
};

#endif // REMOVESPECIFICENTRIESDIALOGADAPTER_H
