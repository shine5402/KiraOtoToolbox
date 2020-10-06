#ifndef OTOFILEMULTIPLEOPENWIDGET_H
#define OTOFILEMULTIPLEOPENWIDGET_H

#include <QWidget>
#include "../models/otofilelistmodel.h"

namespace Ui {
    class OtoFileMultipleLoadWidget;
}

class OtoFileMultipleLoadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OtoFileMultipleLoadWidget(QWidget *parent = nullptr);
    ~OtoFileMultipleLoadWidget();
    void reset();
    int count() const;
    QList<OtoEntryList> entryLists() const;
    QStringList fileNames() const;

private slots:
    void showOtoList();
    void appendOtoFile();
    void removeOtoFile();
private:
    Ui::OtoFileMultipleLoadWidget *ui;
    int currentRow();
    OtoFileListModel* model = new OtoFileListModel;
    void refreshButtonEnableState();
signals:
    void dataChanged();
};

#endif // OTOFILEMULTIPLEOPENWIDGET_H
