#include "tooloptions.h"
#include <otoentry.h>

QVariant ToolOptions::getOption(const QString& key, const QVariant& defaultValue, bool* matched) const
{
    if (matched)
        *matched = options.contains(key);
    return options.value(key, defaultValue);
}

void ToolOptions::setOption(const QString& key, const QVariant& value, bool* replaced)
{
    if (replaced)
        *replaced = options.contains(key);
    options.insert(key, value);
}

bool ToolOptions::removeOption(const QString& key)
{
    return options.remove(key);
}

QStringList ToolOptions::getOptionKeys() const
{
    return options.keys();
}

ToolOptions::ToolOptions(const ToolOptions& options): QObject(options.parent())
{
    this->options = options.options;
}

const ToolOptions& ToolOptions::operator =(const ToolOptions& options)
{
    if (options != *this)
        this->options = options.options;
    return *this;
}

bool ToolOptions::operator==(const ToolOptions& rhs) const
{
    return rhs.options == options;
}

bool ToolOptions::operator!=(const ToolOptions& rhs) const
{
    return !(*this == rhs);
}

void ToolOptions::combine(const ToolOptions& rhs, const QString& prefix)
{
    doCombine(*this, rhs, prefix);
}

void ToolOptions::doCombine(ToolOptions& lhs, const ToolOptions& rhs, const QString& prefix)
{
    for (auto i = rhs.options.begin(); i != rhs.options.end(); ++i){
        lhs.options.insert(prefix + i.key(), i.value());
    }
}

ToolOptions ToolOptions::combine(const ToolOptions& lhs, const ToolOptions& rhs, const QString& prefix)
{
    auto result = lhs;
    doCombine(result, rhs, prefix);
    return result;
}

ToolOptions ToolOptions::extract(const QString& prefix) const
{
    ToolOptions result;
    for (auto i = options.begin(); i != options.end(); ++i){
        if (i.key().startsWith(prefix))
        {
            result.setOption(OtoEntryFunctions::removePrefix(i.key(), prefix), i.value());
        }
    }
    return result;
}

ToolOptions ToolOptions::unCombine(const QString& prefix)
{
    auto extractResult = extract(prefix);
    for (auto i = extractResult.options.begin(); i != options.end(); ++i){
        removeOption(prefix + i.key());
    }
    return extractResult;
}
