#ifndef REMOVEAFFIXOPTIONWIDGET_H
#define REMOVEAFFIXOPTIONWIDGET_H

#include <QWidget>

namespace Ui {
    class RemoveAffixOptionWidget;
}

class RemoveAffixOptionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RemoveAffixOptionWidget(QWidget *parent = nullptr);
    ~RemoveAffixOptionWidget();

private:
    Ui::RemoveAffixOptionWidget *ui;
};

#endif // REMOVEAFFIXOPTIONWIDGET_H
