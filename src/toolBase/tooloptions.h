#ifndef TOOLOPTIONS_H
#define TOOLOPTIONS_H

#include <QObject>
#include <QHash>
#include <QVariant>

class ToolOptions : public QObject {
    Q_OBJECT
public:
    explicit ToolOptions(QObject* parent) : QObject(parent){};
    QVariant getOption(const QString& key, const QVariant& defaultValue = {}, bool* matched = nullptr) const;
    void setOption(const QString& key, const QString& value, bool* replaced = nullptr);
    bool removeOption(const QString& key);
    QStringList getOptionKeys() const;
protected:
    QHash<QString, QVariant> options;
};

#endif // TOOLOPTIONS_H
