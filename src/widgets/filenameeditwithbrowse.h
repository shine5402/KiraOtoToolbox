#ifndef FILENAMEEDITWITHBROWSE_H
#define FILENAMEEDITWITHBROWSE_H

#include <QWidget>

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

    QString getFileName() const;
    void setFileName(const QString& value);
    Purpose getPurpose() const;
    void setPurpose(const Purpose& value);
private:
    Ui::FileNameEditWithBrowse *ui;
    Purpose purpose = Open;
    void openFilePathBrowse();
    void saveFilePathBrowse();
private slots:
    void browse();
};

#endif // FILENAMEEDITWITHBROWSE_H
