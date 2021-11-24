#ifndef FILENAMEEDITWITHBROWSE_H
#define FILENAMEEDITWITHBROWSE_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
    class FileNameEditWithBrowse;
}

class FileNameEditWithBrowse : public QWidget
{
    Q_OBJECT

public:
    enum Purpose{Open, Save};
    Q_ENUM(Purpose);

    explicit FileNameEditWithBrowse(QWidget *parent = nullptr);
    ~FileNameEditWithBrowse();

    QString fileName() const;
    void setFileName(const QString& value);

    QStringList fileNames() const;
    void setFileNames(const QStringList& value);

    Purpose getPurpose() const;
    void setPurpose(const Purpose& value);
    QString getCaption() const;
    void setCaption(const QString& value);

    QString getDir() const;
    void setDir(const QString& value);

    QString getFilter() const;
    void setFilter(const QString& value);

    QFileDialog::Options getOptions() const;
    void setOptions(const QFileDialog::Options& value);

    void setParameters(const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString *selectedFilter = nullptr, QFileDialog::Options options = QFileDialog::Options());

    QString* getSelectedFilter() const;
    void setSelectedFilter(QString* value);

    bool isMultipleMode() const;
    void setMultipleMode(bool multipleMode);

    QString getMultipleModeSeparator() const;
    void setMultipleModeSeparator(const QString& value);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    Ui::FileNameEditWithBrowse *ui;
    Purpose purpose = Open;

    bool m_multipleMode;
    QString multipleModeSeparator = "||";

    void openFilePathBrowse();
    void saveFilePathBrowse();

    QString caption{};
    QString dir{};
    QString filter{};
    QString* selectedFilter = nullptr;
    QFileDialog::Options options = QFileDialog::Options();

    QString processFileName(const QString& fileName) const;

private slots:
    void browse();

signals:
    void browseTriggered();
};


class FileNameEditWithOpenBrowse : public FileNameEditWithBrowse{
    Q_OBJECT
public:
    explicit FileNameEditWithOpenBrowse(QWidget *parent = nullptr);
};

class FileNameEditWithSaveBrowse : public FileNameEditWithBrowse{
    Q_OBJECT
public:
    explicit FileNameEditWithSaveBrowse(QWidget *parent = nullptr);
};
#endif // FILENAMEEDITWITHBROWSE_H
