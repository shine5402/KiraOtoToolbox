#ifndef REPLACEFILENAMEADAPTER_H
#define REPLACEFILENAMEADAPTER_H

#include <toolBase/tooldialogadapter.h>

class ReplaceFileNameAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ReplaceFileNameAdapter(QObject *parent = nullptr);
    DEFINE_TOOL_NAME("Replace file name (and rename file)");
};

#endif // REPLACEFILENAMEADAPTER_H
