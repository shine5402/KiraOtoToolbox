#ifndef REMOVEDSTRINGINFO_H
#define REMOVEDSTRINGINFO_H
#include <QtCore>
#include <QString>

class RemovedStringInfo
{
public:
    enum AffixType{Prefix, Suffix};
    RemovedStringInfo(AffixType type, int id, QString value);
    RemovedStringInfo(const RemovedStringInfo& rhs);
    const RemovedStringInfo& operator=(const RemovedStringInfo& rhs);
    bool operator==(const RemovedStringInfo& rhs) const;
    bool operator!=(const RemovedStringInfo& rhs) const;

    AffixType type() const;
    int id() const;
    QString value() const;

private:
    AffixType m_type;
    int m_id;
    QString m_value;

};

#endif // REMOVEDSTRINGINFO_H
