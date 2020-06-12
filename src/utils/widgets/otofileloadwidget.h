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

    void setFileName(const QString& fileName);
    QString fileName() const;
    OtoEntryList getEntryList() const;
    bool isEntryListReaded() const;
private:
    Ui::OtoFileLoadWidget *ui;
    OtoEntryList entryList = {};
    bool entryListReaded = false;
private slots:
    void loadOtoFile();
    void showOtoListDialog();
signals:
    void loaded();
};

#endif // OTOFILELOADWIDGET_H
