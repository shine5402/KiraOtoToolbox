#ifndef TOOLEXCEPTION_H
#define TOOLEXCEPTION_H

#include <QException>
#include <QString>

class ToolException : QException
{
public:
    ToolException(QString info) : info_(std::move(info)) {};
    ToolException(const ToolException &other) : info_(other.info_) {}
    QString info() const;

private:
    QString info_;
};

#endif // TOOLEXCEPTION_H
