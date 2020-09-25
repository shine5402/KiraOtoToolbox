#ifndef OTOFILEMULTIPLESAVEWIDGET_H
#define OTOFILEMULTIPLESAVEWIDGET_H

#include <QWidget>

namespace Ui {
    class OtoFileMultipleSaveWidget;
}

class OtoFileMultipleSaveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OtoFileMultipleSaveWidget(QWidget *parent = nullptr);
    ~OtoFileMultipleSaveWidget();

private:
    Ui::OtoFileMultipleSaveWidget *ui;
};

#endif // OTOFILEMULTIPLESAVEWIDGET_H
