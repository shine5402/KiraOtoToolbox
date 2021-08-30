#ifndef SETALIASDIALOGADAPTER_H
#define SETALIASDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class SetAliasDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE SetAliasDialogAdapter(QObject *parent = nullptr);
    QString getToolName() const override;
};

#endif // SETALIASDIALOGADAPTER_H
