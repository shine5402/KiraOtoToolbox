#include "tooloptions.h"

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

ToolOptions::ToolOptions(const ToolOptions& options)
{
    this->options = options.options;
}

void ToolOptions::operator=(const ToolOptions& options)
{
    if (options != *this)
        this->options = options.options;
}

bool ToolOptions::operator==(const ToolOptions& rhs) const
{
    return rhs.options == options;
}

bool ToolOptions::operator!=(const ToolOptions& rhs) const
{
    return !(*this == rhs);
}
