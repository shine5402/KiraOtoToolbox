#ifndef ADDAFFIXDIALOGADAPTER_H
#define ADDAFFIXDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class AddAffixDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE AddAffixDialogAdapter(QObject* parent = nullptr);
    QString getWindowTitle() const override;
};

#endif // ADDAFFIXDIALOGADAPTER_H
