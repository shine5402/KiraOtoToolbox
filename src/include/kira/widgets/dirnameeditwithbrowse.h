#ifndef DIRNAMEEDITWITHBROWSE_H
#define DIRNAMEEDITWITHBROWSE_H

#include <QWidget>
#include <QFileDialog>

class QLineEdit;
class QPushButton;

class DirNameEditWithBrowse : public QWidget
{
    Q_OBJECT
public:
    explicit DirNameEditWithBrowse(QWidget *parent = nullptr);

    QString dirName() const;
    void setDirName(const QString& value);

    QString getCaption() const;
    void setCaption(const QString& value);

    QFileDialog::Options getOptions() const;
    void setOptions(const QFileDialog::Options& value);

private:
    QLineEdit* dirNameEdit;
    QString caption{};
    QFileDialog::Options options = QFileDialog::ShowDirsOnly;
    QPushButton* browseButton;
private slots:
    void onBrowse();
signals:
    void browseTriggered();
    void dropTriggered();
    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent* event) override;
    void changeEvent(QEvent* event) override;
};

#endif // DIRNAMEEDITWITHBROWSE_H
