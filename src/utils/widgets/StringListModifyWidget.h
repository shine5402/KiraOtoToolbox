#ifndef STRINGLISTMODIFYWIDGET_H
#define STRINGLISTMODIFYWIDGET_H

#include <QStringListModel>
#include <QWidget>

namespace Ui {
class StringListModifyWidget;
}

class StringListModifyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StringListModifyWidget(QWidget *parent = nullptr);
    ~StringListModifyWidget();

    QStringList getData() const;
    void setData(const QStringList &value);

protected:
    void changeEvent(QEvent *event) override;

private:
    Ui::StringListModifyWidget *ui;

    QStringListModel *model = new QStringListModel();

private slots:
    void addRow();
    void deleteCurrentRow();
    void openMultiLineEdit();

signals:
    void dataModified();
};

#endif // STRINGLISTMODIFYWIDGET_H
