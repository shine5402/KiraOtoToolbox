#ifndef OVERLAPBATCHSETDIALOGADAPTER_H
#define OVERLAPBATCHSETDIALOGADAPTER_H

#include <QWidget>
#include "toolBase/tooldialogadapter.h"


class OverlapBatchSetDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    explicit OverlapBatchSetDialogAdapter(QObject *parent = nullptr);
    void setupSpecificUIWidgets(QLayout *rootLayout) override;
    bool processOtoList(const OtoEntryList &srcOtoList, OtoEntryList &resultOtoList, OtoEntryList &secondSaveOtoList, const ToolOptions *abstractOptions, QWidget *dialogParent) override;
};

#endif // OVERLAPBATCHSETDIALOGADAPTER_H
