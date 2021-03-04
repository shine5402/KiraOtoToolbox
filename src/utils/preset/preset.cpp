#include "preset.h"

Preset::Preset(QObject *parent) : QObject(parent)
{

}

QString Preset::name() const
{
    return m_name;
}

void Preset::setName(const QString& name)
{
    m_name = name;
    emit nameChanged();
}

const Preset& Preset::operator=(const Preset& rhs)
{
    if (*this != rhs){
        setContent(rhs.content());
        setName(rhs.name());
    }
    return *this;
}

bool Preset::operator==(const Preset& rhs) const
{
    return rhs.name() == name() && rhs.content() == content();
}

bool Preset::operator!=(const Preset& rhs) const
{
    return !(rhs == *this);
}
