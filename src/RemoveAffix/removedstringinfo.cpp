#include "removedstringinfo.h"

RemovedStringInfo::RemovedStringInfo(AffixType type, int id, QString value): m_type(type), m_id(id), m_value(value)
{

}

RemovedStringInfo::RemovedStringInfo(const RemovedStringInfo& rhs)
{
    m_type = rhs.type();
    m_id = rhs.id();
    m_value = rhs.value();
}

const RemovedStringInfo& RemovedStringInfo::operator =(const RemovedStringInfo& rhs)
{
    if (rhs != *this)
    {
        m_type = rhs.type();
        m_id = rhs.id();
        m_value = rhs.value();
    }
    return *this;
}

bool RemovedStringInfo::operator==(const RemovedStringInfo& rhs) const
{
    return m_type == rhs.type() && m_id == rhs.id() && m_value == rhs.value();
}

bool RemovedStringInfo::operator!=(const RemovedStringInfo& rhs) const
{
    return !(*this == rhs);
}

RemovedStringInfo::AffixType RemovedStringInfo::type() const
{
    return m_type;
}

QString RemovedStringInfo::value() const
{
    return m_value;
}

int RemovedStringInfo::id() const
{
    return m_id;
}
