#ifndef OPTIONCONTAINER_H
#define OPTIONCONTAINER_H

#include <QObject>
#include <QHash>
#include <QVariant>

class OptionContainer : public QObject {
    Q_OBJECT

public:
    OptionContainer():QObject(nullptr){};
    explicit OptionContainer(QObject* parent) : QObject(parent){};
    QVariant getOption(const QString& key, const QVariant& defaultValue = {}, bool* matched = nullptr) const;
    void setOption(const QString& key, const QVariant& value, bool* replaced = nullptr);
    bool removeOption(const QString& key);
    int count() const{
        return options.count();
    }
    bool exists(const QString& key) const{
        return options.find(key) != options.end();
    }
    bool isEmpty() const{
        return options.isEmpty();
    }
    void clear(){
        options.clear();
    }
    QStringList getOptionKeys() const;
    OptionContainer(const OptionContainer& options);
    OptionContainer(OptionContainer&& other);
    const OptionContainer& operator=(const OptionContainer& options);
    bool operator==(const OptionContainer& rhs) const;
    bool operator!=(const OptionContainer& rhs) const;
    void combine(const OptionContainer& rhs, const QString& prefix = {});
    static OptionContainer combine(const OptionContainer& lhs, const OptionContainer& rhs, const QString& prefix = {});
    OptionContainer extract(const QString& prefix) const;
    OptionContainer unCombine(const QString& prefix);
protected:
    QHash<QString, QVariant> options;
private:
    static void doCombine(OptionContainer& lhs, const OptionContainer& rhs, const QString& prefix);
};

#endif // OPTIONCONTAINER_H
