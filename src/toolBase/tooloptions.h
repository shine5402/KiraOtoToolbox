#ifndef TOOLOPTIONS_H
#define TOOLOPTIONS_H

#include <QObject>
#include <QHash>
#include <QVariant>

class ToolOptions : public QObject {
    Q_OBJECT

public:
    explicit ToolOptions(QObject* parent = nullptr) : QObject(parent){};
    QVariant getOption(const QString& key, const QVariant& defaultValue = {}, bool* matched = nullptr) const;
    void setOption(const QString& key, const QVariant& value, bool* replaced = nullptr);
    bool removeOption(const QString& key);
    QStringList getOptionKeys() const;
    ToolOptions(const ToolOptions& options);
    void operator=(const ToolOptions& options);
    bool operator==(const ToolOptions& rhs) const;
    bool operator!=(const ToolOptions& rhs) const;
    void combine(const ToolOptions& rhs, const QString& prefix = {});
    static ToolOptions combine(const ToolOptions& lhs, const ToolOptions& rhs, const QString& prefix = {});
    ToolOptions extract(const QString& prefix) const;
    ToolOptions unCombine(const QString& prefix);
protected:
    QHash<QString, QVariant> options;
private:
    static void doCombine(ToolOptions& lhs, const ToolOptions& rhs, const QString& prefix);
};

#endif // TOOLOPTIONS_H
