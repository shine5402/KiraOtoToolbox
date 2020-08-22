#ifndef OTOFILESAVEWIDGET_H
#define OTOFILESAVEWIDGET_H

#include <QWidget>

namespace Ui {
    class OtoFileSaveWidget;
}

class OtoFileSaveWidget : public QWidget
{
    Q_OBJECT

#ifdef SHINE5402OTOBOX_TEST
    friend class UtilWidgetsTest;
#endif

public:
    explicit OtoFileSaveWidget(QWidget *parent = nullptr);
    ~OtoFileSaveWidget();

    bool isSaveToSrc() const;
    bool isSaveToCustom() const;
    QString fileName() const;
    bool isSecondFileNameUsed() const;
    QString secondFileName() const;

    void setSaveToSrc();
    void setSaveToCustom();
    void setFileName(const QString& value);
    void setSecondFileNameUsed(bool value);
    void setSecondFileName(const QString& value);

    bool isSecondFileNameAvailable() const;
    void setSecondFileNameAvailable(bool value);
    void setSecondFileNameCheckBoxText(const QString& text);

    QString secondFileNameUsage() const;
    void setSecondFileNameUsage(const QString& value);

private:
    Ui::OtoFileSaveWidget *ui;
    bool m_secondFileNameAvailable = false;
    void refreshSecondFileNameWidgetVisible();
    QString m_secondFileNameUsage{};
};

class OtoFileSaveWidgetWithSecondFileName : public OtoFileSaveWidget {
    Q_OBJECT

public:
    explicit OtoFileSaveWidgetWithSecondFileName(QWidget *parent = nullptr);
};

class OtoFileSaveWidgetWithSecondFileNameAsDeleted : public OtoFileSaveWidgetWithSecondFileName {
    Q_OBJECT

public:
    explicit OtoFileSaveWidgetWithSecondFileNameAsDeleted(QWidget *parent = nullptr);
};
#endif // OTOFILESAVEWIDGET_H
