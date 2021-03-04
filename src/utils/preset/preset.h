#ifndef PRESET_H
#define PRESET_H

#include <QObject>
#include <QVariant>

class Preset : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariant content READ content WRITE setContent NOTIFY contentChanged)

public:
    explicit Preset(QObject *parent = nullptr);
    Preset(const Preset& rhs);

    virtual QVariant content() const = 0;
    virtual void setContent(const QVariant& content) = 0;

    QString name() const;
    void setName(const QString& name);

    const Preset& operator= (const Preset& rhs);
    bool operator==(const Preset& rhs) const;
    bool operator!=(const Preset& rhs) const;

private:
    QString m_name;

signals:
    void nameChanged();
    void contendChanged();
};

#endif // PRESET_H
