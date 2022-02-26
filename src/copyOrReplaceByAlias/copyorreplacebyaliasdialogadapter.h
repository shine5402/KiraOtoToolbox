#ifndef COPYORREPLACEBYALIASDIALOGADAPTER_H
#define COPYORREPLACEBYALIASDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class CopyOrReplaceByAliasDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit CopyOrReplaceByAliasDialogAdapter(QObject* parent);
    DEFINE_TOOL_NAME("Copy/Replace by alias")
};

#endif // COPYORREPLACEBYALIASDIALOGADAPTER_H
