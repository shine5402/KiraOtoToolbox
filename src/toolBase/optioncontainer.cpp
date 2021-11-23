#include "optioncontainer.h"
#include <OtoUtil/otoentry.h>

QVariant OptionContainer::getOption(const QString& key, const QVariant& defaultValue, bool* matched) const
{
    if (matched)
        *matched = options.contains(key);
    return options.value(key, defaultValue);
}

void OptionContainer::setOption(const QString& key, const QVariant& value, bool* replaced)
{
    if (replaced)
        *replaced = options.contains(key);
    options.insert(key, value);
}

bool OptionContainer::removeOption(const QString& key)
{
    return options.remove(key);
}

QStringList OptionContainer::getOptionKeys() const
{
    return options.keys();
}

OptionContainer::OptionContainer(const OptionContainer& options): QObject(options.parent())
{
    this->options = options.options;
}

OptionContainer::OptionContainer(OptionContainer&& other)
{
    this->options = other.options;
    other.options = {};
}

const OptionContainer& OptionContainer::operator =(const OptionContainer& options)
{
    if (options != *this)
        this->options = options.options;
    return *this;
}

bool OptionContainer::operator==(const OptionContainer& rhs) const
{
    return rhs.options == options;
}

bool OptionContainer::operator!=(const OptionContainer& rhs) const
{
    return !(*this == rhs);
}

void OptionContainer::combine(const OptionContainer& rhs, const QString& prefix)
{
    doCombine(*this, rhs, prefix);
}

void OptionContainer::doCombine(OptionContainer& lhs, const OptionContainer& rhs, const QString& prefix)
{
    for (auto i = rhs.options.begin(); i != rhs.options.end(); ++i){
        lhs.options.insert(prefix + i.key(), i.value());
    }
}

OptionContainer OptionContainer::combine(const OptionContainer& lhs, const OptionContainer& rhs, const QString& prefix)
{
    auto result = lhs;
    doCombine(result, rhs, prefix);
    return result;
}

OptionContainer OptionContainer::extract(const QString& prefix) const
{
    OptionContainer result;
    for (auto i = options.begin(); i != options.end(); ++i){
        if (i.key().startsWith(prefix))
        {
            result.setOption(OtoEntryFunctions::removePrefix(i.key(), prefix), i.value());
        }
    }
    return result;
}

OptionContainer OptionContainer::unCombine(const QString& prefix)
{
    auto extractResult = extract(prefix);
    for (auto i = extractResult.options.begin(); i != options.end(); ++i){
        removeOption(prefix + i.key());
    }
    return extractResult;
}
