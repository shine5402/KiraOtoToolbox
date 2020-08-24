#ifndef REMOVEBLANKOPTIONWIDGET_H
#define REMOVEBLANKOPTIONWIDGET_H

#include "toolBase/tooloptionwidget.h"

class QCheckBox;

class RemoveBlankOptionWidget : public ToolOptionWidget
{
    Q_OBJECT
public:
    RemoveBlankOptionWidget(QWidget* parent = nullptr);
    ToolOptions getOptions() const override;
    void setOptions(const ToolOptions &options) override;
private:
    QCheckBox* ignoreRightCheckBox = nullptr;
};

#endif // REMOVEBLANKOPTIONWIDGET_H
