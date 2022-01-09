#include <kira/filesystem.h>
#include <QStringList>
#include <QStack>
#include <QDir>

QStringList getAbsoluteWAVFileNamesUnder(QString rootDirName, bool recursive){
        QStack<QString> dirNameStack;
        dirNameStack.append(rootDirName);

        QStringList result;
        while (!dirNameStack.isEmpty()){
            auto currentDirName = dirNameStack.pop();
            QDir currentDir{currentDirName};

            auto wavEntryList = currentDir.entryList({"*.wav"}, QDir::Files | QDir::NoDotAndDotDot);
            for (const auto& entry : std::as_const(wavEntryList)){
               result.append(currentDir.filePath(entry));
            }
            if (!recursive)
                break;

            auto dirsToPush = currentDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
            for (const auto& i : std::as_const(dirsToPush)){
                dirNameStack.push(currentDir.filePath(i));
            }
        }
        return result;
    }
