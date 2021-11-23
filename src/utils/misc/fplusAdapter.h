#ifndef FPLUSADAPTER_H
#define FPLUSADAPTER_H
#include <QList>
#include <fplus/fplus.hpp>

// This file contains some utils that adapt Qt's container to FunctionalPlus.
// It only contains needed adapters to solve the problem I found, so it is very incomplete.

namespace fplus {
    template <typename ContainerIn, typename ContainerOut = typename ContainerIn::value_type>
    ContainerOut concat_qt_adapt_internal(const ContainerIn& lists){
        ContainerOut result;
        for (auto i : lists){
            result.append(i);
        }
        return result;
    }
    template <typename ValueType>
    QList<ValueType> concat(const QList<QList<ValueType>>& lists)
    {
        return concat_qt_adapt_internal(lists);
    }
    template <typename ValueType>
    QVector<ValueType> concat(const QVector<QVector<ValueType>>& lists)
    {
        return concat_qt_adapt_internal(lists);
    }

    namespace internal {
        template<class T> struct has_order<QVector<T>> : public std::true_type{};
        template<class T> struct has_order<QList<T>> : public std::true_type{};

        template<class T, class NewT, int SizeOffset> struct same_cont_new_t<QVector<T>, NewT, SizeOffset>{typedef class QVector<NewT> type;};
        template<class T, class NewT, int SizeOffset> struct same_cont_new_t<QList<T>, NewT, SizeOffset>{typedef class QList<NewT> type;};

        template<typename T>
        struct can_self_assign<QVector<T>>
        {
            using type = std::integral_constant<bool, true>;
        };
        template<typename T>
        struct can_self_assign<QList<T>>
        {
            using type = std::integral_constant<bool, true>;
        };

        //It seems that fplus want to reuse a rvalue const QVector<T>...
        template <typename T>
        struct can_reuse<const QVector<T>>
        {
            using dContainer = typename std::decay<QVector<T>>::type;
            using can_assign = can_self_assign_t<typename dContainer::value_type>;
            using cannot_reuse = std::integral_constant<bool, true>;
            using value = reuse_container_bool_t<bool, can_assign::value && !cannot_reuse::value>;
        };
        template <typename T>
        struct can_reuse<const QList<T>>
        {
            using dContainer = typename std::decay<QVector<T>>::type;
            using can_assign = can_self_assign_t<typename dContainer::value_type>;
            using cannot_reuse = std::integral_constant<bool, true>;
            using value = reuse_container_bool_t<bool, can_assign::value && !cannot_reuse::value>;
        };
    }

    template <typename T>
    T get_just_or_default(const maybe<T>& maybe){
        return maybe.is_just() ? maybe.unsafe_get_just() : T{};
    }

    template <typename T>
    T get_just_or_default(const maybe<T>& maybe, const T& default_value){
        return maybe.is_just() ? maybe.unsafe_get_just() : default_value;
    }
}

#endif // FPLUSADAPTER_H
