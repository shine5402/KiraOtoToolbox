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
    void operator=(const RemovedStringInfo& rhs);
    bool operator==(const RemovedStringInfo& rhs) const;
    bool operator!=(const RemovedStringInfo& rhs) const;

    AffixType getType() const;
    QString getValue() const;

private:
    AffixType type;
    QString value;
    int id;
};

#endif // REMOVEDSTRINGINFO_H
