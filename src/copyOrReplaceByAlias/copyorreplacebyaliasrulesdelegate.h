#ifndef COPYORREPLACEBYALIASRULESDELEGATE_H
#define COPYORREPLACEBYALIASRULESDELEGATE_H

#include <QStyledItemDelegate>

class CopyOrReplaceByAliasRulesDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CopyOrReplaceByAliasRulesDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
public:
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
};

#endif // COPYORREPLACEBYALIASRULESDELEGATE_H
