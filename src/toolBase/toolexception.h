#ifndef TOOLEXCEPTION_H
#define TOOLEXCEPTION_H

#include <QString>
#include <QException>

class ToolException : QException
{
public:
    ToolException(QString info) : info_(std::move(info)){};
    ToolException(const ToolException& other);
    QString info() const;
private:
    QString info_;
};

#endif // TOOLEXCEPTION_H
