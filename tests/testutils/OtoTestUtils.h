#ifndef OTOTESTUTILS_H
#define OTOTESTUTILS_H

#include "otoUtils/OtoEntry.h"
#include "toolBase/OptionContainer.h"

inline OtoEntry makeEntry(QString fileName, QString alias, double left, double consonant, double right,
                          double preUtterance, double overlap)
{
    return OtoEntry(fileName, alias, left, consonant, right, preUtterance, overlap);
}

inline OptionContainer makeOptions(std::initializer_list<QPair<QString, QVariant>> pairs)
{
    OptionContainer opts;
    for (const auto &[key, value] : pairs) {
        opts.setOption(key, value);
    }
    return opts;
}

// Japanese CV (solo-tone) voicebank — 5 entries covering vowel, stop, nasal, and regular consonant patterns
// Values reflect real oto conventions: stops have negative overlap, regular consonants use ~1/3 overlap
inline OtoEntryList makeCvVoicebank()
{
    return {
        makeEntry("あ.wav", "あ", 0.0, 300.0, 1200.0, 150.0, 0.0),       // vowel
        makeEntry("か.wav", "か", 300.0, 500.0, 1400.0, 500.0, -100.0),   // stop consonant
        makeEntry("き.wav", "き", 200.0, 450.0, 1300.0, 450.0, 50.0),     // regular consonant
        makeEntry("た.wav", "た", 280.0, 480.0, 1350.0, 480.0, -80.0),    // stop consonant
        makeEntry("ん.wav", "ん", 0.0, 200.0, 1000.0, 100.0, 0.0),        // moraic nasal (vowel pattern)
    };
}

// Japanese VCV (continuous-tone) voicebank with pitch suffix C4
// Alias format: "{leading vowel} {target kana}{pitch}"
// Leading "-" indicates rest/silence at phrase start
inline OtoEntryList makeVcvVoicebank()
{
    return {
        makeEntry("あ_C4.wav", "- あC4", 0.0, 300.0, 1400.0, 100.0, 0.0),
        makeEntry("い_C4.wav", "a いC4", 300.0, 500.0, 1600.0, 500.0, 50.0),
        makeEntry("う_C4.wav", "i うC4", 200.0, 450.0, 1300.0, 450.0, 60.0),
        makeEntry("え_C4.wav", "u えC4", 250.0, 480.0, 1500.0, 480.0, 55.0),
        makeEntry("お_C4.wav", "e おC4", 220.0, 420.0, 1400.0, 420.0, 50.0),
        makeEntry("か_C4.wav", "a かC4", 350.0, 550.0, 1450.0, 550.0, 60.0),
        makeEntry("き_C4.wav", "i きC4", 300.0, 500.0, 1500.0, 500.0, 55.0),
    };
}

// CVVC voicebank — CV entries (plain alias) + VC entries (space-separated alias)
inline OtoEntryList makeCvvcVoicebank()
{
    return {
        makeEntry("か.wav", "か", 200.0, 450.0, 1300.0, 450.0, 50.0),    // CV
        makeEntry("き.wav", "き", 180.0, 420.0, 1250.0, 420.0, 45.0),    // CV
        makeEntry("く.wav", "く", 220.0, 460.0, 1350.0, 460.0, 55.0),    // CV
        makeEntry("a k.wav", "a k", 0.0, 80.0, 400.0, 80.0, 30.0),       // VC
        makeEntry("i k.wav", "i k", 0.0, 75.0, 380.0, 75.0, 25.0),       // VC
        makeEntry("u k.wav", "u k", 0.0, 85.0, 420.0, 85.0, 28.0),       // VC
    };
}

// Chinese CV-VV (拡張整音) voicebank — CV part + VV part (coda restoration)
// CV entries cut before the coda; VV entries add coda back
inline OtoEntryList makeCvVvVoicebank()
{
    return {
        makeEntry("lan.wav", "lan", 100.0, 350.0, 900.0, 350.0, 50.0),   // CV (cut before -n)
        makeEntry("_an.wav", "_an", 0.0, 70.0, 500.0, 70.0, 23.0),        // VV (-n coda)
        makeEntry("kan.wav", "kan", 120.0, 370.0, 920.0, 370.0, 55.0),   // CV
        makeEntry("kang.wav", "kang", 110.0, 380.0, 950.0, 380.0, 55.0), // CV
        makeEntry("_ang.wav", "_ang", 0.0, 75.0, 520.0, 75.0, 25.0),      // VV (-ng coda)
        makeEntry("bie.wav", "bie", 130.0, 360.0, 880.0, 360.0, 60.0),   // CV
    };
}

// Entries with all-zero params and empty aliases — used for blank-entry removal testing
inline OtoEntryList makeBlankEntryList()
{
    return {
        makeEntry("blank1.wav", "", 0.0, 0.0, 0.0, 0.0, 0.0),
        makeEntry("blank2.wav", "", 0.0, 0.0, 0.0, 0.0, 0.0),
        makeEntry("blank3.wav", "", 0.0, 0.0, 0.0, 0.0, 0.0),
    };
}

// Entries with duplicate aliases — used for dedup testing
inline OtoEntryList makeDuplicateAliasList()
{
    return {
        makeEntry("a1.wav", "test", 0.0, 300.0, 1000.0, 150.0, 50.0),
        makeEntry("a2.wav", "test", 0.0, 320.0, 1050.0, 160.0, 50.0),
        makeEntry("a3.wav", "test", 0.0, 310.0, 1020.0, 155.0, 50.0),
        makeEntry("a4.wav", "other", 0.0, 400.0, 1200.0, 200.0, 60.0),
        makeEntry("a5.wav", "other", 0.0, 390.0, 1180.0, 195.0, 60.0),
    };
}

#endif // OTOTESTUTILS_H
