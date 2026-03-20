#include "otoentry.h"
#include <utility>
#include <QHash>
#include <QDebug>
#include <QMetaEnum>
#include <QSaveFile>


OtoEntry::OtoEntry(QString fileName,
                   QString alias,
                   double left,
                   double consonant,
                   double right,
                   double preUtterance,
                   double overlap,
                   QObject *parent)
    : QObject(parent), fileName_(std::move(fileName)), alias_(std::move(alias)),
      left_(left), consonant_(consonant),right_(right),
      preUtterance_(preUtterance),overlap_(overlap),valid_(true)
{

}

const int OtoEntry::OtoParameterCount = QMetaEnum::fromType<OtoEntry::OtoParameter>().keyCount();

OtoEntry::OtoEntry(const OtoEntry& other) : QObject(other.parent())
{
    fileName_ = other.fileName_;
    alias_ = other.alias_;
    left_ = other.left_;
    consonant_ = other.consonant_;
    right_ = other.right_;
    preUtterance_ = other.preUtterance_;
    overlap_ = other.overlap_;

    m_error = other.m_error;
    valid_ = other.valid_;
}

OtoEntry& OtoEntry::operator=(const OtoEntry& rhs)
{
    if (*this != rhs)
    {
        fileName_ = rhs.fileName_;
        alias_ = rhs.alias_;
        left_ = rhs.left_;
        consonant_ = rhs.consonant_;
        right_ = rhs.right_;
        preUtterance_ = rhs.preUtterance_;
        overlap_ = rhs.overlap_;

        m_error = rhs.m_error;
        valid_ = rhs.valid_;
    }
    return *this;
}

QString OtoEntry::toString(int precision) const
{
    return QString("%1=%2,%3,%4,%5,%6,%7")
            .arg(fileName_, alias_)
            .arg(left_,0,'f',precision)
            .arg(consonant_,0,'f',precision)
            .arg(right_,0,'f',precision)
            .arg(preUtterance_,0,'f',precision)
            .arg(overlap_,0,'f',precision);
}

bool OtoEntry::operator==(const OtoEntry& rhs) const
{
    return fileName() == rhs.fileName() && alias() == rhs.alias()
            && left() == rhs.left() && consonant() == rhs.consonant()
            && right() == rhs.right() && preUtterance() == rhs.preUtterance()
            && overlap() == rhs.overlap();
}

bool OtoEntry::operator!=(const OtoEntry& rhs) const
{
    return !(*this == rhs);
}

void OtoEntry::setError(OtoEntry::OtoEntryError error)
{
    m_error = error;
    setValid(false);
}

void OtoEntry::setValid(bool valid)
{
    valid_ = valid;
}

QString OtoEntry::fileName() const
{
    return fileName_;
}

QString OtoEntry::alias() const
{
    return alias_;
}

double OtoEntry::left() const
{
    return left_;
}

void OtoEntry::setLeft(double value)
{
    left_ = value;
    emit leftChanged();
}

double OtoEntry::consonant() const
{
    return consonant_;
}

void OtoEntry::setConsonant(double value)
{
    consonant_ = value;
    emit consonantChanged();
}

double OtoEntry::right() const
{
    return right_;
}

void OtoEntry::setRight(double value)
{
    right_ = value;
    emit rightChanged();
}

double OtoEntry::preUtterance() const
{
    return preUtterance_;
}

void OtoEntry::setPreUtterance(double value)
{
    preUtterance_ = value;
    emit preUtteranceChanged();
}

double OtoEntry::overlap() const
{
    return overlap_;
}

void OtoEntry::setOverlap(double value)
{
    overlap_ = value;
    emit overlapChanged();
}

QVariant OtoEntry::getParameter(OtoEntry::OtoParameter parameter) const
{
    switch (parameter)
    {
        case FileName: return fileName();
        case Alias: return alias();
        case Left: return left();
        case Consonant: return consonant();
        case Right: return right();
        case PreUtterance: return preUtterance();
        case Overlap: return overlap();
    }
    return {};
}

QVariant OtoEntry::getParameter(OtoEntry::OtoParameterOrder parameter) const
{
    switch (parameter) {
        case FILENAME: return fileName();
        case ALIAS: return alias();
        case LEFT: return left();
        case CONSONANT: return consonant();
        case RIGHT: return right();
        case PREUTTERANCE: return preUtterance();
        case OVERLAP: return overlap();
    }
    return {};
}

void OtoEntry::setParameter(OtoEntry::OtoParameter parameter, QVariant value)
{
    switch (parameter) {
        case FileName: setFileName(value.toString());break;
        case Alias: setAlias(value.toString());break;
        case Left: setLeft(value.toDouble());break;
        case Consonant: setConsonant(value.toDouble());break;
        case Right: setRight(value.toDouble());break;
        case PreUtterance: setPreUtterance(value.toDouble());break;
        case Overlap: setOverlap(value.toDouble());break;
    }
}

void OtoEntry::setParameter(OtoEntry::OtoParameterOrder parameter, QVariant value)
{
    switch (parameter) {
        case FILENAME: setFileName(value.toString());break;
        case ALIAS: setAlias(value.toString());break;
        case LEFT: setLeft(value.toDouble());break;
        case CONSONANT: setConsonant(value.toDouble());break;
        case RIGHT: setRight(value.toDouble());break;
        case PREUTTERANCE: setPreUtterance(value.toDouble());break;
        case OVERLAP: setOverlap(value.toDouble());break;
    }

}

OtoEntry::OtoParameter OtoEntry::getParameterFlag(OtoEntry::OtoParameterOrder order)
{
    switch (order) {
        case FILENAME: return FileName;
        case ALIAS: return Alias;
        case LEFT: return Left;
        case CONSONANT: return Consonant;
        case RIGHT: return Right;
        case PREUTTERANCE: return PreUtterance;
        case OVERLAP: return Overlap;
    }
    throw std::runtime_error("Invalid OtoParameterOrder");
}

OtoEntry::OtoParameterOrder OtoEntry::getParameterOrder(OtoEntry::OtoParameter flag)
{
    switch (flag) {
        case FileName: return FILENAME;
        case Alias: return ALIAS;
        case Left: return LEFT;
        case Consonant: return CONSONANT;
        case Right: return RIGHT;
        case PreUtterance: return PREUTTERANCE;
        case Overlap: return OVERLAP;
    }
    throw std::runtime_error("Invalid OtoParameter");
}

QString OtoEntry::errorString(OtoEntryError error)
{
    static const QHash<OtoEntryError,QString> errorStrings{
        {UnknownError, "Unknown Error"},
        {FileNameSeparatorNotFound, "The separator between fileName and alias are not found."},
        {LeftConvertFailed, "Convert left string to double failed."},
        {ConsonantConvertFailed, "Convert consonant string to double failed."},
        {RightConvertFailed, "Convert right string to double failed."},
        {PreUtteranceConvertFailed, "Convert preUtterance string to double failed."},
        {OverlapConvertFailed, "Convert overlap string to double failed."},
        {EmptyOtoString, "The provided string is empty"},
        {EmptyFileName, "The fileName is empty"},
    };

    return errorStrings.value(error);
}

OtoEntry OtoEntry::fromString(const QString& str, bool* ok, OtoEntryError* error)
{
    //Init
    if (ok)
        *ok = false;
    OtoEntry result;
    auto setError = [error](OtoEntryError err) mutable{
        if (error)
            *error = err;
    };
    setError(UnknownError);

    if (str.isEmpty())
    {
        setError(EmptyOtoString);
        return result;
    }
    auto fileNameEndIndex = str.indexOf("=");
    if (fileNameEndIndex != -1)
    {
        result.setFileName(str.left(fileNameEndIndex));
        if (result.fileName().isEmpty())
        {
            setError(EmptyFileName);
            return result;
        }
        auto parameterString = str.mid(fileNameEndIndex + 1);
        result.setAlias(parameterString.section(",",0,0));

        constexpr int parameterCount = 5;
        std::array<bool,parameterCount> doubleConvertOks{};
        enum parameterID{LEFT, CONSONANT, RIGHT, PREUTTERANCE, OVERLAP};

        result.setLeft(parameterString.section(",",1,1).toDouble(&doubleConvertOks[parameterID::LEFT]));
        result.setConsonant(parameterString.section(",",2,2).toDouble(&doubleConvertOks[parameterID::CONSONANT]));
        result.setRight(parameterString.section(",",3,3).toDouble(&doubleConvertOks[parameterID::RIGHT]));
        result.setPreUtterance(parameterString.section(",",4,4).toDouble(&doubleConvertOks[parameterID::PREUTTERANCE]));
        result.setOverlap(parameterString.section(",",5,5).toDouble(&doubleConvertOks[parameterID::OVERLAP]));

        for (int i = parameterID::LEFT; i <= parameterID::OVERLAP; i++)
        {
            if (!doubleConvertOks.at(i))
            {
                switch (i) {
                    case LEFT: setError(LeftConvertFailed);break;
                    case CONSONANT: setError(ConsonantConvertFailed);break;
                    case RIGHT: setError(RightConvertFailed);break;
                    case PREUTTERANCE: setError(PreUtteranceConvertFailed);break;
                    case OVERLAP: setError(OverlapConvertFailed);break;
                }
                return result;
            }
        }
    }
    else{
        setError(FileNameSeparatorNotFound);
        return result;
    }
    if (ok)
        *ok = true;
    return result;
}

OtoEntry OtoEntry::fromString(const QString& str)
{
    bool ok = false;
    OtoEntryError error = UnknownError;
    auto result = fromString(str, &ok, &error);
    if (!ok)
    {
        throw ParseError(error);
    }
    return result;
}

void OtoEntry::setAlias(const QString& value)
{
    alias_ = value;
    emit aliasChanged();
}

void OtoEntry::setFileName(const QString& value)
{
    fileName_ = value;
    emit fileNameChanged();
}




QString OtoEntryFunctions::removePitchSuffix(QString alias, const QString& bottomPitch, const QString& topPitch, Qt::CaseSensitivity cs, CharacterCase pitchRangeCharacterCase, QString* pitchRemoved)
{
    auto pitchRange = getPitchStringRange(bottomPitch, topPitch, pitchRangeCharacterCase);
    for (const auto& pitch : pitchRange)
    {
        bool removed = false;
        auto result = removeSuffix(alias, pitch, cs, &removed);
        if (removed)
        {
            if (pitchRemoved)
                *pitchRemoved = pitch;
            return result;
        }
    }
    return alias;
}

QString OtoEntryFunctions::removePitchPrefix(QString alias, const QString& bottomPitch, const QString& topPitch, Qt::CaseSensitivity cs, OtoEntryFunctions::CharacterCase pitchRangeCharacterCase, QString* pitchRemoved)
{
    auto pitchRange = getPitchStringRange(bottomPitch, topPitch, pitchRangeCharacterCase);
    for (const auto& pitch : pitchRange)
    {
        bool removed = false;
        auto result = removePrefix(alias, pitch, cs, &removed);
        if (removed)
        {
            if (pitchRemoved)
                *pitchRemoved = pitch;
            return result;
        }
    }
    return alias;
}

QStringList OtoEntryFunctions::getPitchStringRange(const QString& bottomPitch, const QString& topPitch, CharacterCase cs){
    const QStringList PitchNameOrder = [&]() -> QStringList{
            switch (cs) {
            case Upper: return {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
            case Lower: return {"c", "c#", "d", "d#", "e", "f", "f#", "g", "g#", "a", "a#", "b"};
}
            return {};
}();
    //const QString PitchUpSignOrder = "## ### ";
    if (bottomPitch.isEmpty() || topPitch.isEmpty())
        return {};

    auto getPitchNameID = [&PitchNameOrder] (const QString& str) -> int{
        for (int i = 0; i < PitchNameOrder.count(); ++i)
        {
            if (str.startsWith(PitchNameOrder.at(i), Qt::CaseInsensitive))
                return i;
        }
        return -1;
    };
    auto bottomPitchName = getPitchNameID(bottomPitch);
    auto topPitchName = getPitchNameID(topPitch);

    if (bottomPitchName == -1 || topPitchName == -1)
        return {};

    bool bottomOctaveConvertOk, topOctaveConvertOk;
    auto bottomOctave = bottomPitch.mid(1).toInt(&bottomOctaveConvertOk);
    auto topOctave = topPitch.mid(1).toInt(&topOctaveConvertOk);

    if (!(bottomOctaveConvertOk && topOctaveConvertOk))
        return {};

    QStringList pitchStringRange;
    for (auto currentOctave = bottomOctave; currentOctave <= topOctave; ++currentOctave)
    {
        int startPitchName = 0, endPitchName = PitchNameOrder.count() - 1;
        if (currentOctave == bottomOctave)
            startPitchName = bottomPitchName;
        if (currentOctave == topOctave)
            endPitchName = topPitchName;
        for (auto currentPitchName = startPitchName; currentPitchName <= endPitchName; ++currentPitchName)
        {
            pitchStringRange.append(QString("%1%2").arg(PitchNameOrder.at(currentPitchName)).arg(currentOctave));
        }
    }
    return pitchStringRange;
}

QString OtoEntryFunctions::removeSuffix(QString string, const QString& suffix, Qt::CaseSensitivity cs, bool* removed)
{
    auto suffixPos = string.lastIndexOf(suffix, -1, cs);
    if (removed)
        *removed = suffixPos != -1;
    if (suffixPos != -1)
    {
        return string.remove(suffixPos, suffix.count());
    }
    return string;
}

QString OtoEntryFunctions::removePrefix(QString string, const QString& prefix, Qt::CaseSensitivity cs, bool* removed)
{
    auto prefixPos = string.indexOf(prefix, 0, cs);
    if (removed)
        *removed = prefixPos != -1;
    if (prefixPos != -1)
    {
        return string.remove(prefixPos, prefix.count());
    }
    return string;
}

QString OtoEntryFunctions::getDigitSuffix(const QString& string, int* position, bool considerNegative)
{
    QString result{};
    for (int current = string.count() - 1; current >= 0; --current)
    {
        if (auto c = string.at(current);c.isDigit()){
            result.prepend(c);
        }
        else
        {
            if (considerNegative && current >= 0 && string.at(current) == '-')
            {
                result.prepend(string.at(current));
                current -= 1;
            }
            if (position)
            {
                *position = (current != string.count() - 1) ? current + 1 : -1;
            }
            break;
        }
    }
    return result;
}

bool OtoEntryFunctions::writeOtoListToFile(const QString& fileName, const OtoEntryList& entryList, int precision, QFileDevice::FileError* error, QString* errorString , QTextCodec* textCodec,
                                           bool directWriteFallback){
    QSaveFile file(fileName);
    file.setDirectWriteFallback(directWriteFallback);
    bool successed = false;
    if (file.open(QFile::Text | QFile::WriteOnly)){
        QStringList otoStringList;
        for (const auto &i : entryList)
        {
            otoStringList.append(i.toString(precision));
        }
        file.write(textCodec->makeEncoder()->fromUnicode(otoStringList.join("\n")));
        successed = file.commit();
    }
    if (!successed)
    {
        if (error)
            *error = file.error();
        if (errorString)
            *errorString = file.errorString();
    }
    return successed;
}


QString OtoEntryFunctions::removeDigitSuffix(QString string, int* position, bool considerNegative, bool* removed)
{
    return removeSuffix(string, getDigitSuffix(string, position, considerNegative), Qt::CaseInsensitive, removed);
}
