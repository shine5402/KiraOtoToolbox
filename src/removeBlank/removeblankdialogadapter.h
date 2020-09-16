#ifndef REMOVEBLANKDIALOGADAPTER_H
#define REMOVEBLANKDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class RemoveBlankDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE RemoveBlankDialogAdapter(QObject* parent = nullptr);
    QString getToolName() const override;
};

#endif // REMOVEBLANKDIALOGADAPTER_H
