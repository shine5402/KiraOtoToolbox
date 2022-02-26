#ifndef REPLACERULESDELEGATE_H
#define REPLACERULESDELEGATE_H

#include <QStyledItemDelegate>

class ReplaceRulesDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ReplaceRulesDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
public:
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
};

#endif // REPLACERULESDELEGATE_H
