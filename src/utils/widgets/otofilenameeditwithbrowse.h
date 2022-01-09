#ifndef OTOFILENAMEEDITWITHBROWSE_H
#define OTOFILENAMEEDITWITHBROWSE_H

#include <QWidget>
#include <kira/widgets/filenameeditwithbrowse.h>

class OtoFileNameEditWithBrowse : public FileNameEditWithBrowse
{
    Q_OBJECT
public:
    explicit OtoFileNameEditWithBrowse(QWidget *parent = nullptr);
    void setParametersByPurpose(const Purpose& value);
signals:

};

class OtoFileNameEditWithOpenBrowse : public OtoFileNameEditWithBrowse {
    Q_OBJECT
public:
    explicit OtoFileNameEditWithOpenBrowse(QWidget *parent = nullptr);
};

class OtoFileNameEditWithSaveBrowse : public OtoFileNameEditWithBrowse {
    Q_OBJECT
public:
    explicit OtoFileNameEditWithSaveBrowse(QWidget *parent = nullptr);
};

#endif // OTOFILENAMEEDITWITHBROWSE_H
