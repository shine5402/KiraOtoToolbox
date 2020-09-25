#ifndef OVERLAPBATCHSETDIALOGADAPTER_H
#define OVERLAPBATCHSETDIALOGADAPTER_H

#include <QWidget>
#include "toolBase/tooldialogadapter.h"


class OverlapBatchSetDialogAdapter : public ToolDialogAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit OverlapBatchSetDialogAdapter(QObject *parent = nullptr);
    QString getToolName() const override;
};

#endif // OVERLAPBATCHSETDIALOGADAPTER_H
