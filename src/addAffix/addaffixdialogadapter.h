#ifndef ADDAFFIXDIALOGADAPTER_H
#define ADDAFFIXDIALOGADAPTER_H

#include <toolBase/tooldialogadapter.h>

class AddAffixDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    AddAffixDialogAdapter(QObject* parent = nullptr);
    void setupSpecificUIWidgets(QLayout *rootLayout) override;
    bool doWorkAdapter(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions *options, QWidget *dialogParent) override;
    QString getWindowTitle() const override;
};

#endif // ADDAFFIXDIALOGADAPTER_H
