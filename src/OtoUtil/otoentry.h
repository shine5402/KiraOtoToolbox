#ifndef OTOENTRY_H
#define OTOENTRY_H

#include "../QtUTAULibrarys_global.h"
#include <QObject>

/// OtoEntry 定义了一条原音设定条目。
class QTUTAULIBRARYS_EXPORT OtoEntry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged);
    Q_PROPERTY(QString alias READ alias WRITE setAlias NOTIFY aliasChanged);
    Q_PROPERTY(double left READ left WRITE setLeft NOTIFY leftChanged);
    Q_PROPERTY(double consonant READ consonant WRITE setConsonant NOTIFY consonantChanged);
    Q_PROPERTY(double right READ right WRITE setRight NOTIFY rightChanged);
    Q_PROPERTY(double preUtterance READ preUtterance WRITE setPreUtterance NOTIFY preUtteranceChanged);
    Q_PROPERTY(double overlap READ overlap WRITE setOverlap NOTIFY overlapChanged);
    Q_PROPERTY(bool valid MEMBER m_valid);

public:
    OtoEntry(QString m_fileName,
             QString m_alias,
             double m_left,
             double m_consonant,
             double m_right,
             double m_preUtterance,
             double m_overlap,
             QObject *parent = nullptr);
    explicit OtoEntry(const QString& otoString);
    OtoEntry(const OtoEntry& other);

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

    /*!
    @brief 该条条目的文件名属性。
    fileName 告知UTAU引擎时应该在哪个文件中寻找对应原音块。
    这个文件名相对于oto.ini所在的文件夹。
    @see void setFileName(const QString& value)
*/
    QString fileName() const;

    /*!
    @brief 设置该条条目的文件名属性。
    @see QString fileName() const
*/
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

    OtoEntryError error() const;
    QString errorString() const;

    QString toString() const;

    bool isValid() const{
        return m_valid;
    }

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
    QString m_fileName {};
    QString m_alias {};
    double m_left {};
    double m_consonant {};
    double m_right {};
    double m_preUtterance {};
    double m_overlap {};

    OtoEntryError m_error{UnknownError};
    void setError(OtoEntryError error);
    bool m_valid = false;

    void setValid(bool valid);
};

namespace OtoEntryFunctions {
    //After Qt 5.14, can use Q_NAMESAPCE_EXPORT and Q_ENUM to register this enum with the meta-object system, it can provide additional feature. But as I use 5.13, I can not use the feature. May change in future.
    enum CharacterCase{
        Upper, Lower
    };

    QTUTAULIBRARYS_EXPORT QStringList getPitchStringRange(const QString& bottomPitch, const QString& topPitch, CharacterCase characterCase = Upper);
    QTUTAULIBRARYS_EXPORT QString removePitchSuffix(QString alias, const QString& bottomPitch, const QString& topPitch, Qt::CaseSensitivity cs = Qt::CaseInsensitive, CharacterCase pitchRangeCharacterCase = CharacterCase::Upper);
    QTUTAULIBRARYS_EXPORT QString removeSuffix(QString string, const QString& suffix, Qt::CaseSensitivity cs = Qt::CaseSensitive);
    QTUTAULIBRARYS_EXPORT QString getDigitSuffix(const QString& string, int* position = nullptr);
}


#endif // OTOENTRY_H
