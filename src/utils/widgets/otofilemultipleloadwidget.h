#ifndef OTOFILEMULTIPLEOPENWIDGET_H
#define OTOFILEMULTIPLEOPENWIDGET_H

#include <QWidget>

namespace Ui {
    class OtoFileMultipleLoadWidget;
}

class OtoFileMultipleLoadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OtoFileMultipleLoadWidget(QWidget *parent = nullptr);
    ~OtoFileMultipleLoadWidget();

private slots:

private:
    Ui::OtoFileMultipleLoadWidget *ui;
};

#endif // OTOFILEMULTIPLEOPENWIDGET_H
