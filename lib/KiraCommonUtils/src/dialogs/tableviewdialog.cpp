#include <kira/dialogs/tableviewdialog.h>
#include <QVBoxLayout>

TableViewDialog::TableViewDialog(QWidget* parent, QAbstractTableModel* model, const QString& title,
                                 const QString& labelText, QDialogButtonBox::StandardButtons standardButtons)
    : QDialog(parent)
{
    setWindowTitle(title);

    auto layout = new QVBoxLayout(this);

    layout->addWidget(label);
    setLabel(labelText);

    layout->addWidget(tableView);
    setModel(model);
    setStandardButtons(standardButtons);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    setLayout(layout);
}

void TableViewDialog::setLabel(const QString& text)
{
    label->setText(text);
    if (text.isEmpty())
        label->hide();
    else
        label->show();
}

void TableViewDialog::setStandardButtons(QDialogButtonBox::StandardButtons buttons)
{
    buttonBox->setStandardButtons(buttons);
}

QAbstractTableModel* TableViewDialog::getModel() const
{
    return dynamic_cast<QAbstractTableModel*>(tableView->model());
}

void TableViewDialog::setModel(QAbstractTableModel* value)
{
    tableView->setModel(value);
}

QSize TableViewDialog::sizeHint() const
{
    return QSize(750, 550);
}
