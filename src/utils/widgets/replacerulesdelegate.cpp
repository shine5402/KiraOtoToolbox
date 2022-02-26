#include "replacerulesdelegate.h"
#include <QComboBox>
#include "replacerule.h"

ReplaceRulesDelegate::ReplaceRulesDelegate(QObject* parent):QStyledItemDelegate(parent)
{

}


QWidget* ReplaceRulesDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.column() == 2){
        auto strategyComboBox = new QComboBox(parent);
        strategyComboBox->addItems({
                                       ReplaceRule::getStrategyString(ReplaceRule::Exact),
                                       ReplaceRule::getStrategyString(ReplaceRule::Partial),
                                       ReplaceRule::getStrategyString(ReplaceRule::Regex)
                                   });
        strategyComboBox->setAutoFillBackground(true);
        return strategyComboBox;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ReplaceRulesDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (index.column() == 2){
        auto strategyComboBox = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(editor);
        strategyComboBox->setCurrentIndex(index.data(Qt::EditRole).toInt());
        return;
    }
    return QStyledItemDelegate::setEditorData(editor, index);
}

void ReplaceRulesDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    if (index.column() == 2){
        auto strategyComboBox = qobject_cast<QComboBox*>(editor);
        Q_ASSERT(editor);
        model->setData(index, strategyComboBox->currentIndex(), Qt::EditRole);
        return;
    }
    return QStyledItemDelegate::setModelData(editor, model, index);
}
