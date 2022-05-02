#ifndef FPLUSADAPTER_H
#define FPLUSADAPTER_H
#include <QList>
#include <fplus/fplus.hpp>
#include <QJsonArray>
#include <QVariantList>
#include <QtGlobal>

// This file contains some utils that adapt Qt's container to FunctionalPlus.
// To use, include it with fplus, or just replace fplus with this file.
// It only contains needed adapters to solve the problem I found, so it is very incomplete.
// It also contains some utils making my usuage easier.

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
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    template <typename ValueType>
    QVector<ValueType> concat(const QVector<QVector<ValueType>>& lists)
    {
        return concat_qt_adapt_internal(lists);
    }
#endif
    template <typename F, typename T>
    auto transform_and_concat(F f, const QList<T>& xs)
    {
        internal::trigger_static_asserts<internal::unary_function_tag, F, typename QList<T>::value_type>();
        return concat_qt_adapt_internal(transform(f, xs));
    }
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    template <typename F, typename T>
    auto transform_and_concat(F f, const QVector<T>& xs)
    {
        internal::trigger_static_asserts<internal::unary_function_tag, F, typename QVector<T>::value_type>();
        return concat_qt_adapt_internal(transform(f, xs));
    }
#endif
    template <typename F>
    auto transform_and_concat(F f, const QStringList& xs)
    {
        internal::trigger_static_asserts<internal::unary_function_tag, F, typename QStringList::value_type>();
        return concat_qt_adapt_internal(transform(f, xs));
    }

    template <typename Key, typename T, typename Pred>
    QHash<Key,T> map_keep_if(Pred pred, const QHash<Key,T>& map)
    {
        QHash<Key,T> result;
        for (auto it = map.begin(); it != map.end; ++it)
        {
            if (internal::invoke(pred, it.key()))
            {
                result.insert(it.key(), it.value());
            }
        }
        return result;
    }

    template <typename Key, typename T, typename Pred>
    QMap<Key,T> map_keep_if(Pred pred, const QMap<Key,T>& map)
    {
        QMap<Key,T> result;
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            if (internal::invoke(pred, it.key()))
            {
                result.insert(it.key(), it.value());
            }
        }
        return result;
    }

    namespace internal {
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
        template<class T> struct has_order<QVector<T>> : public std::true_type{};
#endif
        template<class T> struct has_order<QList<T>> : public std::true_type{};
        template<> struct has_order<QJsonArray> : public std::true_type{};
        template<> struct has_order<QVariantList> : public std::true_type{};


        //same_container_new_type, used for construct a new container of same elem type.
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
        template<class T, class NewT, int SizeOffset> struct same_cont_new_t<QVector<T>, NewT, SizeOffset>{typedef class QVector<NewT> type;};
#endif
        template<class T, class NewT, int SizeOffset> struct same_cont_new_t<QList<T>, NewT, SizeOffset>{typedef class QList<NewT> type;};
        template<class NewT, int SizeOffset> struct same_cont_new_t<QVariantList, NewT, SizeOffset>{typedef class QList<NewT> type;};
        template<class NewT, int SizeOffset> struct same_cont_new_t<QStringList, NewT, SizeOffset>{typedef class QList<NewT> type;};
        template<class NewT, int SizeOffset> struct same_cont_new_t<QJsonArray, NewT, SizeOffset>{typedef class QList<NewT> type;};

        template<class Key, class T, class NewKey, class NewVal> struct SameMapTypeNewTypes<QMap<Key, T>, NewKey, NewVal> { typedef QMap<NewKey, NewVal> type; };
        template<class Key, class T, class NewKey, class NewVal> struct SameMapTypeNewTypes<QHash<Key, T>, NewKey, NewVal> { typedef QHash<NewKey, NewVal> type; };

#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
        template<typename T>
        struct can_self_assign<QVector<T>>
        {
            using type = std::integral_constant<bool, true>;
        };
#endif
        template<typename T>
        struct can_self_assign<QList<T>>
        {
            using type = std::integral_constant<bool, true>;
        };

        //It seems that fplus want to reuse a rvalue const QVector<T>...
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
        template <typename T>
        struct can_reuse<const QVector<T>>
        {
            using dContainer = typename std::decay<QVector<T>>::type;
            using can_assign = can_self_assign_t<typename dContainer::value_type>;
            using cannot_reuse = std::integral_constant<bool, true>;
            using value = reuse_container_bool_t<bool, can_assign::value && !cannot_reuse::value>;
        };
#endif
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

    template <typename ContainerIn>
    auto zipWithNext(ContainerIn xs){
        return zip(drop_last(1, xs), drop(1, xs));
    }
}

#endif // FPLUSADAPTER_H
