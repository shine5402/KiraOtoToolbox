#ifndef REMOVEAFFIXDIALOGADAPTER_H
#define REMOVEAFFIXDIALOGADAPTER_H
#include "toolBase/tooldialogadapter.h"

//TODO:
class RemoveAffixDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    RemoveAffixDialogAdapter(QWidget* parent = nullptr);
    void setupSpecificUIWidgets(QLayout *rootLayout) override;
    QString getWindowTitle() const override;
};

#endif // REMOVEAFFIXDIALOGADAPTER_H
