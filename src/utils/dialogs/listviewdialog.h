#ifndef LISTVIEWDIALOG_H
#define LISTVIEWDIALOG_H

#include <QDialog>
#include <QListView>
#include <QDialogButtonBox>
#include <QLabel>

class ListViewDialog : public QDialog
{
    Q_OBJECT
public:
    ListViewDialog(QWidget* parent = nullptr, QAbstractListModel* model = nullptr, const QString& title = {}, const QString& labelText = {}, QDialogButtonBox::StandardButtons standardButtons = QDialogButtonBox::Ok);
    void setLabel(const QString& text);
    void setStandardButtons(QDialogButtonBox::StandardButtons buttons);
    QAbstractListModel* getModel() const;
    void setModel(QAbstractListModel* value);
    QSize sizeHint() const override;

    int currentRow() const;
    QList<int> selectedRows() const;

    QAbstractItemView::SelectionMode selectionMode() const;
    void setSelectionMode(QAbstractItemView::SelectionMode mode);

    void setSelectionBehavior(QAbstractItemView::SelectionBehavior behavior);
    QAbstractItemView::SelectionBehavior selectionBehaviour() const;
protected:
    QAbstractListModel* model = nullptr;
    QLabel* label = new QLabel(this);
    QListView* listView = new QListView(this);
    QDialogButtonBox* buttonBox = new QDialogButtonBox(this);
};

#endif // LISTVIEWDIALOG_H
