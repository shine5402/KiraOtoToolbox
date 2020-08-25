#ifndef CHAINDIALOGADAPTER_H
#define CHAINDIALOGADAPTER_H

#include "toolBase/tooldialogadapter.h"

class ChainDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE ChainDialogAdapter(QObject* parent = nullptr);
    QString getWindowTitle() const override;
};

#endif // CHAINDIALOGADAPTER_H
