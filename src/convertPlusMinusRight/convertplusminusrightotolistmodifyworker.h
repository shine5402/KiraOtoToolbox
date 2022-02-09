#ifndef CONVERTPLUSMINUSRIGHTOTOLISTMODIFYWORKER_H
#define CONVERTPLUSMINUSRIGHTOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>

class ConvertPlusMinusRightOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    class FileNotFoundException : ToolException {
    public:
        FileNotFoundException(const QString& fileName) :
            ToolException(tr("The file \"%1\" don't exist. Please check and try again.").arg(fileName)),
            fileName_(fileName){};
        QString fileName() const{
            return fileName_;
        }
    private:
        QString fileName_;
    };

    class FileCannotReadException : ToolException {
    public:
        FileCannotReadException(const QString& fileName) :
            ToolException(tr("Cannot open file \"%1\", or it contains invalid data. Please check and try again.").arg(fileName)),
            fileName_(fileName){};
        QString fileName() const{
            return fileName_;
        }
    private:
        QString fileName_;
    };

    class InvalidRightValue : ToolException {
    public:
        InvalidRightValue(const OtoEntry& entry, double calculatedRight) :
            ToolException(tr("Invalid right value\"%1\" has been calculated for oto \"%2\". Please check and try again.").arg(calculatedRight).arg(entry.toString())),
            entry_(entry), calculatedRight_(calculatedRight){};

        OtoEntry entry() const{
            return entry_;
        };
        double calculatedRight() const{
            return calculatedRight_;
        }
    private:
        OtoEntry entry_;
        double calculatedRight_;
    };

    Q_INVOKABLE explicit ConvertPlusMinusRightOtoListModifyWorker(QObject* parent = nullptr);
    bool doWork(const OtoEntryList& srcOtoList, OtoEntryList& resultOtoList, OtoEntryList& secondSaveOtoList, const OptionContainer& options) override;
};

#endif // CONVERTPLUSMINUSRIGHTOTOLISTMODIFYWORKER_H
