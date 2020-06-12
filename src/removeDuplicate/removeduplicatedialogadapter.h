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
    bool doWork(const OtoFileLoadWidget *loadWidget, const OtoFileSaveWidget *saveWidget,
                const ToolOptionWidget *optionWidget, QWidget* dialogParent) override;
};

#endif // REMOVEDUPLICATEDIALOGADAPTER_H
