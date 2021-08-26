#ifndef SETALIASTOOLDIALOGADAPTER_H
#define SETALIASTOOLDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class SetAliasToolDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE SetAliasToolDialogAdapter(QObject *parent = nullptr);
    QString getToolName() const override;
};

#endif // SETALIASTOOLDIALOGADAPTER_H
