#ifndef OTOFILELOADWIDGET_H
#define OTOFILELOADWIDGET_H

#include <QWidget>
#include <OtoUtil/otoentry.h>

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
    void reset();
    void load();

    void pretendLoaded(const QString& fileName, const OtoEntryList& entryList);
private:
    Ui::OtoFileLoadWidget *ui;
    OtoEntryList entryList = {};
    bool entryListReaded = false;


    void setUpLoadedUI();
private slots:
    void loadOtoFile();
    void showOtoListDialog();
signals:
    void loaded();
    void resetted();
};

#endif // OTOFILELOADWIDGET_H
