#ifndef NOTDOANYTHINGOPTIONWIDGET_H
#define NOTDOANYTHINGOPTIONWIDGET_H

#include <toolBase/tooloptionwidget.h>

class NotDoAnythingOptionWidget : public ToolOptionWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit NotDoAnythingOptionWidget(QWidget *parent = nullptr);

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const;
    void setOptions(const OptionContainer& options);
};

#endif // NOTDOANYTHINGOPTIONWIDGET_H
