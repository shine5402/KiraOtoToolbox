#include "copyorreplacebyaliasrulesdelegate.h"
#include <QComboBox>
#include "copyorreplacebyaliasrule.h"

CopyOrReplaceByAliasRulesDelegate::CopyOrReplaceByAliasRulesDelegate(QObject* parent):QStyledItemDelegate(parent)
{

}


QWidget* CopyOrReplaceByAliasRulesDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.column() == 2){
        auto strategyComboBox = new QComboBox(parent);
        strategyComboBox->addItems({
                                       CopyOrReplaceByAliasRule::getStrategyString(CopyOrReplaceByAliasRule::Exact),
                                       CopyOrReplaceByAliasRule::getStrategyString(CopyOrReplaceByAliasRule::Partial),
                                       CopyOrReplaceByAliasRule::getStrategyString(CopyOrReplaceByAliasRule::Regex)
                                   });
        strategyComboBox->setAutoFillBackground(true);
        return strategyComboBox;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void CopyOrReplaceByAliasRulesDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (index.column() == 2){
        auto strategyComboBox = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(editor);
        strategyComboBox->setCurrentIndex(index.data(Qt::EditRole).toInt());
        return;
    }
    return QStyledItemDelegate::setEditorData(editor, index);
}

void CopyOrReplaceByAliasRulesDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    if (index.column() == 2){
        auto strategyComboBox = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(editor);
        model->setData(index, strategyComboBox->currentIndex(), Qt::EditRole);
        return;
    }
    return QStyledItemDelegate::setModelData(editor, model, index);
}
