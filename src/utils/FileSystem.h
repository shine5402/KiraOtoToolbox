#ifndef KIRA_FILESYSTEM_H
#define KIRA_FILESYSTEM_H

#include <QString>

//TODO: make universal for other file extension
QStringList getAbsoluteWAVFileNamesUnder(QString rootDirName, bool recursive = false);

#endif // KIRA_FILESYSTEM_H