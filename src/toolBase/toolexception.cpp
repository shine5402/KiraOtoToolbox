#include "toolexception.h"

ToolException::ToolException(const ToolException& other)
{
    info_ = other.info_;
}

QString ToolException::info() const {
    return info_;
}
