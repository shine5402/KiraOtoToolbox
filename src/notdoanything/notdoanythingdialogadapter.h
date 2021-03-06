#ifndef NOTDOANYTHINGDIALOGADAPTER_H
#define NOTDOANYTHINGDIALOGADAPTER_H

#include "toolBase/tooldialogadapter.h"

class NotDoAnythingDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit NotDoAnythingDialogAdapter(QObject *parent = nullptr);
    QString getToolName() const override;
};

#endif // NOTDOANYTHINGDIALOGADAPTER_H
