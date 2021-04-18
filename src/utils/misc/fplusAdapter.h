#ifndef FPLUSADAPTER_H
#define FPLUSADAPTER_H
#include <QList>

namespace fplus {
    template <typename ValueType>
    QList<ValueType> concat(const QList<QList<ValueType>>& lists)
    {
        QList<ValueType> result;
        for (auto i : lists){
            result.append(i);
        }
        return result;
    }
}

#endif // FPLUSADAPTER_H
