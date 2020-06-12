#ifndef STRINGLISTMODIFYWIDGET_H
#define STRINGLISTMODIFYWIDGET_H

#include <QWidget>
#include <QStringListModel>

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
    void setData(const QStringList& value);

private:
    Ui::StringListModifyWidget *ui;

    QStringListModel* model = new QStringListModel();
private slots:
    void addRow();
    void deleteCurrentRow();
};

#endif // STRINGLISTMODIFYWIDGET_H
