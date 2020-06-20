#include "otolistshowvaluechangemodel.h"
#include <QMetaEnum>

OtoListShowValueChangeModel::OtoListShowValueChangeModel(OtoEntryList* oldEntryList, OtoEntryList* newEntryList,
                                                         OtoEntry::OtoParameters changedParamters, QObject *parent)
    : QAbstractTableModel(parent),
      oldEntryList(oldEntryList), newEntryList(newEntryList),
      changedParameters(changedParamters)
{
    Q_ASSERT(oldEntryList->count() == newEntryList->count());
    refreshHeaderList();
}

QVariant OtoListShowValueChangeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headerList.at(section);
    }

    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
    {
        return QString::number(section + 1);
    }
    return {};
}

int OtoListShowValueChangeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if ((!oldEntryList) || (!newEntryList))
        return 0;

    return oldEntryList->count();
}

int OtoListShowValueChangeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return headerList.count();

}

QVariant OtoListShowValueChangeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole)
    {
        auto oldOto = oldEntryList->at(index.row());
        auto newOto = newEntryList->at(index.row());

        QVariantList dataContents;
        auto meta = QMetaEnum::fromType<OtoEntry::OtoParameter>();
        for (int i = 0; i < meta.keyCount(); ++i){
            auto currentFlag = static_cast<OtoEntry::OtoParameter>(meta.value(i));
            dataContents.append(oldOto.getParameter(currentFlag));
            if (changedParameters.testFlag(currentFlag))
                dataContents.append(newOto.getParameter(currentFlag));
        }

        return (dataContents.at(index.column()));
    }
    return QVariant();
}

void OtoListShowValueChangeModel::refreshHeaderList()
{
    const QHash<OtoEntry::OtoParameter, QString> parameterName = {
        {OtoEntry::FileName, tr("文件名")}, {OtoEntry::Alias, tr("别名")}, {OtoEntry::Left, tr("左")},
        {OtoEntry::Consonant, tr("固定范围")}, {OtoEntry::Right, tr("右")}, {OtoEntry::PreUtterance, tr("先行发声")},
        {OtoEntry::Overlap, tr("重叠")}
    };

    headerList.clear();

    auto meta = QMetaEnum::fromType<OtoEntry::OtoParameter>();
    for (int i = 0; i < meta.keyCount(); ++i){
        const auto currentName = parameterName.value(static_cast<OtoEntry::OtoParameter>(i));
        headerList.append(currentName);
        if (changedParameters.testFlag(static_cast<OtoEntry::OtoParameter>(meta.value(i))))
            headerList.append(QString("新的%1").arg(currentName));
    }
}
