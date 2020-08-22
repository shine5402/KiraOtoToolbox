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
    QString getWindowTitle() const override;
};

#endif // OVERLAPBATCHSETDIALOGADAPTER_H
