#ifndef CV_VCPARTDETACHOPTIONWIDGET_H
#define CV_VCPARTDETACHOPTIONWIDGET_H

#include <QWidget>
#include "../toolBase/tooloptionwidget.h"

namespace Ui {
    class CV_VCPartDetachOptionWidget;
}

class CV_VCPartDetachOptionWidget : public ToolOptionWidget
{
    Q_OBJECT

public:
    explicit CV_VCPartDetachOptionWidget(QWidget *parent = nullptr);
    ~CV_VCPartDetachOptionWidget();

private:
    Ui::CV_VCPartDetachOptionWidget *ui;

    // ToolOptionWidget interface
public:
    OptionContainer getOptions() const override;
    void setOptions(const OptionContainer& options) override;
};

#endif // CV_VCPARTDETACHOPTIONWIDGET_H
