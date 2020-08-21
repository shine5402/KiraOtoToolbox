#ifndef TABLEVIEWDIALOG_H
#define TABLEVIEWDIALOG_H

#include <QDialog>
#include <QAbstractListModel>
#include <QLabel>
#include <QTableView>
#include <QDialogButtonBox>

class TableViewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TableViewDialog(QWidget* parent = nullptr, QAbstractTableModel* model = nullptr, const QString& title = {}, const QString& labelText = {}, QDialogButtonBox::StandardButtons standardButtons = QDialogButtonBox::Ok);
    void setLabel(const QString& text);
    void setStandardButtons(QDialogButtonBox::StandardButtons buttons);
    QAbstractTableModel* getModel() const;
    void setModel(QAbstractTableModel* value);
    QSize sizeHint() const override;

protected:
    QAbstractTableModel* model = nullptr;
    QLabel* label = new QLabel(this);
    QTableView* tableView = new QTableView(this);
    QDialogButtonBox* buttonBox = new QDialogButtonBox(this);
};

#endif // TABLEVIEWDIALOG_H
