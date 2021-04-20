#ifndef CV_VCPARTSPLITOPTIONWIDGET_H
#define CV_VCPARTSPLITOPTIONWIDGET_H

#include <QWidget>
#include "../toolBase/tooloptionwidget.h"

namespace Ui {
    class CV_VCPartSplitOptionWidget;
}

class CV_VCPartSplitOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit CV_VCPartSplitOptionWidget(QWidget *parent = nullptr);
    ~CV_VCPartSplitOptionWidget();

private:
    Ui::CV_VCPartSplitOptionWidget *ui;

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
};

#endif // CV_VCPARTSPLITOPTIONWIDGET_H
