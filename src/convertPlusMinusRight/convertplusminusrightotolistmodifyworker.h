#ifndef CONVERTPLUSMINUSRIGHTOTOLISTMODIFYWORKER_H
#define CONVERTPLUSMINUSRIGHTOTOLISTMODIFYWORKER_H

#include <toolBase/otolistmodifyworker.h>
#include <exception>

class ConvertPlusMinusRightOtoListModifyWorker : public OtoListModifyWorker
{
    Q_OBJECT
public:
    class FileNotFoundException : std::runtime_error{
    public:
        FileNotFoundException(const QString& fileName) :
            std::runtime_error("[ConvertPlusMinusRightOtoListModifyWorker] cannot find file " +
                               fileName.toStdString()), fileName_(fileName){};
        QString fileName() const{
            return fileName_;
        }
    private:
        QString fileName_;
    };

    class FileCannotReadException : std::runtime_error{
    public:
        FileCannotReadException(const QString& fileName) :
            std::runtime_error("[ConvertPlusMinusRightOtoListModifyWorker] cannot read file " +
                               fileName.toStdString()), fileName_(fileName){};
        QString fileName() const{
            return fileName_;
        }
    private:
        QString fileName_;
    };

    class InvalidRightValue : std::runtime_error{
    public:
        InvalidRightValue(const OtoEntry& entry, double calculatedRight) :
            std::runtime_error("[ConvertPlusMinusRightOtoListModifyWorker] Invalid right value"),
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
