#ifndef REMOVEBLANKDIALOGADAPTER_H
#define REMOVEBLANKDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class RemoveBlankDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    RemoveBlankDialogAdapter(QObject* parent = nullptr);
    void setupSpecificUIWidgets(QLayout *rootLayout) override;
    QString getWindowTitle() const override;
};

#endif // REMOVEBLANKDIALOGADAPTER_H
