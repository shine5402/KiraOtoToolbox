#ifndef REMOVEDUPLICATEDIALOGADAPTER_H
#define REMOVEDUPLICATEDIALOGADAPTER_H

#include <QWidget>
#include "toolBase/tooldialogadapter.h"

class RemoveDuplicateDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    explicit RemoveDuplicateDialogAdapter(QObject *parent = nullptr);
    void setupSpecificUIWidgets(QLayout *rootLayout) override;
protected:
    bool doWorkAdapter(const OtoEntryList &otoList, OtoEntryList &otoListWorking, OtoEntryList &secondSaveList, const ToolOptions *abstractOptions, QWidget *dialogParent) override;
};

#endif // REMOVEDUPLICATEDIALOGADAPTER_H
