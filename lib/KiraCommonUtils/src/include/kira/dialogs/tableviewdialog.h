#ifndef TABLEVIEWDIALOG_H
#define TABLEVIEWDIALOG_H

#include <QAbstractListModel>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QTableView>

class TableViewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TableViewDialog(QWidget *parent = nullptr, QAbstractTableModel *model = nullptr, const QString &title = {},
                             const QString &labelText = {},
                             QDialogButtonBox::StandardButtons standardButtons = QDialogButtonBox::Ok);
    void setLabel(const QString &text);
    void setStandardButtons(QDialogButtonBox::StandardButtons buttons);
    QAbstractTableModel *getModel() const;
    void setModel(QAbstractTableModel *value);
    QSize sizeHint() const override;

protected:
    QLabel *label = new QLabel(this);
    QTableView *tableView = new QTableView(this);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
};

#endif // TABLEVIEWDIALOG_H
