#ifndef OTOENTRY_H
#define OTOENTRY_H

#include <QObject>
#include <QFile>
#include <QTextCodec>
#include <QException>

constexpr int OTOENTRY_DEFAULT_PRECISION = 3;

class OtoEntry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged);
    Q_PROPERTY(QString alias READ alias WRITE setAlias NOTIFY aliasChanged);
    Q_PROPERTY(double left READ left WRITE setLeft NOTIFY leftChanged);
    Q_PROPERTY(double consonant READ consonant WRITE setConsonant NOTIFY consonantChanged);
    Q_PROPERTY(double right READ right WRITE setRight NOTIFY rightChanged);
    Q_PROPERTY(double preUtterance READ preUtterance WRITE setPreUtterance NOTIFY preUtteranceChanged);
    Q_PROPERTY(double overlap READ overlap WRITE setOverlap NOTIFY overlapChanged);

public:
    Q_INVOKABLE OtoEntry(QString fileName,
             QString alias,
             double left,
             double consonant,
             double right,
             double preUtterance,
             double overlap,
             QObject *parent = nullptr);

    Q_INVOKABLE OtoEntry(const OtoEntry& other);
    Q_INVOKABLE OtoEntry(){};

    OtoEntry& operator=(const OtoEntry& rhs);

    enum OtoEntryError{
        UnknownError,
        FileNameSeparatorNotFound,
        LeftConvertFailed,
        ConsonantConvertFailed,
        RightConvertFailed,
        PreUtteranceConvertFailed,
        OverlapConvertFailed,
        EmptyOtoString,
        EmptyFileName,
    };
    Q_ENUM(OtoEntryError);

    class ParseError : public QException {
    public:
        ParseError();
        explicit ParseError(OtoEntryError error) : error_(error){};
        OtoEntryError error() const {
            return error_;
        }
    private:
        OtoEntryError error_ = UnknownError;
    };

    enum OtoParameter{
        FileName = 0x1,
        Alias = 0x2,
        Left = 0x4,
        Consonant = 0x8,
        Right = 0x10,
        PreUtterance = 0x20,
        Overlap = 0x40,
    };

    Q_DECLARE_FLAGS(OtoParameters, OtoParameter);
    Q_FLAG(OtoParameter);


    enum OtoParameterOrder{
        FILENAME, ALIAS, LEFT, CONSONANT, RIGHT, PREUTTERANCE, OVERLAP
    };
    Q_ENUM(OtoParameterOrder);

    static const int OtoParameterCount;

    QString fileName() const;

    void setFileName(const QString& value);

    QString alias() const;
    void setAlias(const QString& value);

    double left() const;
    void setLeft(double value);

    double consonant() const;
    void setConsonant(double value);

    double right() const;
    void setRight(double value);

    double preUtterance() const;
    void setPreUtterance(double value);

    double overlap() const;
    void setOverlap(double value);

    QVariant getParameter(OtoParameter parameter) const;
    QVariant getParameter(OtoParameterOrder parameter) const;

    void setParameter(OtoParameter parameter, QVariant value);
    void setParameter(OtoParameterOrder parameter, QVariant value);

    static OtoParameter getParameterFlag(OtoParameterOrder order);
    static OtoParameterOrder getParameterOrder(OtoParameter flag);

    static QString errorString(OtoEntryError error);

    static OtoEntry fromString(const QString& str, bool* ok, OtoEntryError* error);

    //throw exception instead
    Q_INVOKABLE static OtoEntry fromString(const QString& str);
    Q_INVOKABLE QString toString(int precision = OTOENTRY_DEFAULT_PRECISION) const;

    bool operator==(const OtoEntry& rhs) const;
    bool operator!=(const OtoEntry& rhs) const;

signals:
    void fileNameChanged();
    void aliasChanged();
    void leftChanged();
    void consonantChanged();
    void rightChanged();
    void preUtteranceChanged();
    void overlapChanged();

private:
    QString fileName_ {};
    QString alias_ {};
    double left_ {};
    double consonant_ {};
    double right_ {};
    double preUtterance_ {};
    double overlap_ {};

    OtoEntryError m_error{UnknownError};
    void setError(OtoEntryError error);
    bool valid_ = false;

    void setValid(bool valid);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(OtoEntry::OtoParameters);
Q_DECLARE_METATYPE(OtoEntry)

using OtoEntryList = QList<OtoEntry>;
Q_DECLARE_METATYPE(OtoEntryList)
namespace OtoEntryFunctions {
    Q_NAMESPACE
    enum CharacterCase{
        Upper, Lower
    };
    Q_ENUM_NS(CharacterCase)

    QStringList getPitchStringRange(const QString& bottomPitch, const QString& topPitch, CharacterCase characterCase = Upper);
    QString removePitchSuffix(QString alias, const QString& bottomPitch, const QString& topPitch, Qt::CaseSensitivity cs = Qt::CaseInsensitive, CharacterCase pitchRangeCharacterCase = CharacterCase::Upper, QString* pitchRemoved = nullptr);
    QString removePitchPrefix(QString alias, const QString& bottomPitch, const QString& topPitch, Qt::CaseSensitivity cs = Qt::CaseInsensitive, CharacterCase pitchRangeCharacterCase = CharacterCase::Upper, QString* pitchRemoved = nullptr);
    QString removeSuffix(QString string, const QString& suffix, Qt::CaseSensitivity cs = Qt::CaseSensitive, bool* removed = nullptr);
    QString removePrefix(QString string, const QString& prefix, Qt::CaseSensitivity cs = Qt::CaseSensitive, bool* removed = nullptr);
    QString getDigitSuffix(const QString& string, int* position = nullptr, bool considerNegative = false);
    QString removeDigitSuffix(QString string, int* position = nullptr, bool considerNegative = false, bool* removed = nullptr);

    bool writeOtoListToFile(const QString& fileName, const OtoEntryList& entryList, int precision = OTOENTRY_DEFAULT_PRECISION, QFileDevice::FileError* error = nullptr, QString* errorString = nullptr , QTextCodec* textCodec = QTextCodec::codecForName("Shift-JIS"),
                                                  bool directWriteFallback = true);
}


#endif // OTOENTRY_H
