#include <kira/dialogs/listviewdialog.h>
#include <QVBoxLayout>

ListViewDialog::ListViewDialog(QWidget* parent, QAbstractListModel* model, const QString& title, const QString& labelText, QDialogButtonBox::StandardButtons standardButtons) : QDialog(parent)
{
    setWindowTitle(title);

    auto layout = new QVBoxLayout(this);

    layout->addWidget(label);
    setLabel(labelText);

    layout->addWidget(listView);
    listView->setModel(model);
    setStandardButtons(standardButtons);
    layout->addWidget(buttonBox);

    setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    connect(listView, &QListView::doubleClicked, this, &ListViewDialog::dealDblClick);

    setLayout(layout);
}

void ListViewDialog::setLabel(const QString& text)
{
    label->setText(text);
    if (text.isEmpty())
        label->hide();
    else
        label->show();
}

void ListViewDialog::setStandardButtons(QDialogButtonBox::StandardButtons buttons)
{
    buttonBox->setStandardButtons(buttons);
}

QAbstractListModel* ListViewDialog::getModel() const
{
    return model;
}

void ListViewDialog::setModel(QAbstractListModel* value)
{
    model = value;
}

QSize ListViewDialog::sizeHint() const
{
    return QSize(750, 550);
}

int ListViewDialog::currentRow() const
{
    return listView->selectionModel()->currentIndex().row();
}

QList<int> ListViewDialog::selectedRows() const
{
    QList<int> result;
    auto selectedIndexes = listView->selectionModel()->selectedIndexes();
    for (auto i : std::as_const(selectedIndexes)){
        result.append(i.isValid() ? i.row() : -1);
    }
    return result;
}

QAbstractItemView::SelectionMode ListViewDialog::selectionMode() const
{
    return listView->selectionMode();
}

void ListViewDialog::setSelectionMode(QAbstractItemView::SelectionMode mode)
{
    listView->setSelectionMode(mode);
}

void ListViewDialog::setSelectionBehavior(QAbstractItemView::SelectionBehavior behavior)
{
    listView->setSelectionBehavior(behavior);
}

QAbstractItemView::SelectionBehavior ListViewDialog::selectionBehaviour() const
{
    return listView->selectionBehavior();
}

bool ListViewDialog::ifDoubleClickAsAccept() const
{
    return doubleClickAsAccept;
}

void ListViewDialog::setDoubleClickAsAccept(bool value)
{
    doubleClickAsAccept = value;
}

void ListViewDialog::dealDblClick()
{
    if (doubleClickAsAccept)
        accept();
}
