#ifndef REMOVEAFFIXDIALOGADAPTER_H
#define REMOVEAFFIXDIALOGADAPTER_H
#include "toolBase/tooldialogadapter.h"

class RemoveAffixDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    RemoveAffixDialogAdapter(QWidget* parent = nullptr);
    QString getWindowTitle() const override;
};

#endif // REMOVEAFFIXDIALOGADAPTER_H
