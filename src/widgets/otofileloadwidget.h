#ifndef OTOFILELOADWIDGET_H
#define OTOFILELOADWIDGET_H

#include <QWidget>
#include <otoentry.h>

namespace Ui {
    class OtoFileLoadWidget;
}

class OtoFileLoadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OtoFileLoadWidget(QWidget *parent = nullptr);
    ~OtoFileLoadWidget();

private:
    Ui::OtoFileLoadWidget *ui;
    OtoEntryList entryList = {};
    bool entryList_readed = false;
private slots:
    void loadOtoFile();
    void showOtoListDialog();
signals:
    void loaded();
};

#endif // OTOFILELOADWIDGET_H
