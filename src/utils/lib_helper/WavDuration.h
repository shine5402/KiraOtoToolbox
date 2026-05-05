#ifndef WAVDURATION_H
#define WAVDURATION_H

#include <QString>
#include <optional>

#include "dr_libs/dr_wav.h"

namespace WavHelper {

inline std::optional<double> getWavDurationMs(const QString &fileName)
{
    drwav wav;
    drwav_bool32 ok;

#ifdef Q_OS_WIN
    ok = drwav_init_file_w(&wav, reinterpret_cast<const wchar_t *>(fileName.utf16()), nullptr);
#else
    ok = drwav_init_file(&wav, fileName.toUtf8().constData(), nullptr);
#endif

    if (!ok) {
        return std::nullopt;
    }

    double ms = static_cast<double>(wav.totalPCMFrameCount) / wav.sampleRate * 1000.0;
    drwav_uninit(&wav);
    return ms;
}

} // namespace WavHelper

#endif // WAVDURATION_H
