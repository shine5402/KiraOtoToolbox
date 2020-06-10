#ifndef OTOFILESAVEWIDGET_H
#define OTOFILESAVEWIDGET_H

#include <QWidget>

namespace Ui {
    class OtoFileSaveWidget;
}

class OtoFileSaveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OtoFileSaveWidget(QWidget *parent = nullptr);
    ~OtoFileSaveWidget();

    QString fileName() const;
    QString secondFileName() const;

    void setFileName(const QString& value);
    void setSecondFileName(const QString& value);

    bool isSecondFileNameAvailable() const;
    void setSecondFileNameAvailable(bool value);
    void setSecondFileNameCheckBoxText(const QString& text);

private:
    Ui::OtoFileSaveWidget *ui;
    bool secondFileNameAvailable = false;
    void refreshSecondFileNameWidgetVisible();
};

class OtoFileSaveWidgetWithSecondFileName : public OtoFileSaveWidget{
    Q_OBJECT

public:
    explicit OtoFileSaveWidgetWithSecondFileName(QWidget *parent = nullptr);
};

#endif // OTOFILESAVEWIDGET_H
