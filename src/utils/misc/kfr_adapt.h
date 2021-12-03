#ifndef KFR_ADAPT_H
#define KFR_ADAPT_H

#include <kfr/all.hpp>
#include <QFile>
#include <memory>

// Some extra utils added in kfr namespace to provide function needed by my need.

namespace kfr {

    /*
      qt_file_xxx/open_qt_file_for_xxx provide a alternative for kfr'io part, utilizing Qt' QFile IO device.
      Though it's some sort of unnecessary, as kfr already provide portable io out of box, use .toStdWString for bulit-in
      unicode path api is kind of ugly...And Qt has a far more wide cross-platform range than kfr claims.
      So maybe a good idea to port this....IDK, but whatever.
    */

    template <typename T = void>
    struct qt_file_writer : abstract_writer<T>
    {
        qt_file_writer(std::unique_ptr<QFile>&& device) : device(std::move(device)) {}
        ~qt_file_writer() override {}

        using abstract_writer<T>::write;
        size_t write(const T* data, size_t size) final
        {
            return device->write(static_cast<const char*>(data), size);
        }
        imax tell() const final {
            return device->pos();
        }
        bool seek(imax offset, seek_origin origin) final
        {
            qint64 pos;
            switch (origin) {
            case seek_origin::begin: pos = offset; break;
            case seek_origin::current: pos = device->pos() + offset; break;
            case seek_origin::end: pos = device->size() + offset; break;
            }
            return device->seek(pos);
        }
        std::unique_ptr<QFile> device;
    };

    template <typename T = void>
    struct qt_file_reader : abstract_reader<T>
    {
        qt_file_reader(std::unique_ptr<QFile>&& device) : device(std::move(device)) {}
        ~qt_file_reader() override {}
        size_t read(T* data, size_t size) final {
            return device->read(static_cast<char*>(data), size);
        }

        using abstract_reader<T>::read;

        imax tell() const final { return device->pos(); }
        bool seek(imax offset, seek_origin origin) final
        {
            qint64 pos;
            switch (origin) {
            case seek_origin::begin: pos = offset; break;
            case seek_origin::current: pos = device->pos() + offset; break;
            case seek_origin::end: pos = device->size() + offset; break;
            }
            return device->seek(pos);
        }
        std::unique_ptr<QFile> device;
    };

    template <typename T = void>
    inline std::shared_ptr<qt_file_reader<T>> open_qt_file_for_reading(const QString& fileName, bool* openSuccess = nullptr)
    {
        auto device = std::make_unique<QFile>(fileName);
        auto openSuccess_ = device->open(QFile::ReadOnly);
        if (openSuccess)
            *openSuccess = openSuccess_;
        return std::make_shared<qt_file_reader<T>>(std::move(device));
    }

    template <typename T = void>
    inline std::shared_ptr<qt_file_writer<T>> open_qt_file_for_writing(const QString& fileName, bool* openSuccess = nullptr)
    {
        auto device = std::make_unique<QFile>(fileName);
        auto openSuccess_ = device->open(QFile::WriteOnly);
        if (openSuccess)
            *openSuccess = openSuccess_;
        return std::make_shared<qt_file_writer<T>>(std::move(device));
    }

    template <typename T = void>
    inline std::shared_ptr<qt_file_writer<T>> open_qt_file_for_appending(const QString& fileName, bool* openSuccess = nullptr)
    {
        auto device = std::make_unique<QFile>(fileName);
        auto openSuccess_ = device->open(QIODevice::WriteOnly | QFile::Append);
        if (openSuccess)
            *openSuccess = openSuccess_;
        return std::make_shared<qt_file_writer<T>>(std::move(device));
    }

    template <typename sample_t>
    std::unique_ptr<sample_t[]> interleave(univector2d<sample_t> in, size_t& out_size){
        if (in.empty())
        {
            out_size = 0;
            return nullptr;
        }
        qint64 totalSampleCount = 0;
        auto rawDatas = std::make_unique<const sample_t*[]>(in.size());
        for (std::size_t i = 0; i < in.size(); ++i){
            rawDatas.get()[i] = in[i].data();
            totalSampleCount += in[i].size();
        }
        auto interleaveBuffer = std::make_unique<sample_t[]>(totalSampleCount);
        kfr::interleave(interleaveBuffer.get(), rawDatas.get(), in.size(), in[0].size());//in.size -> channel_count, in[0].size() -> length
        out_size = totalSampleCount;
        return interleaveBuffer;
    }
    
    template <typename T>
    size_t write_mutlichannel_wav_file(kfr::audio_writer_wav<T>& writer, const kfr::univector2d<T>& data, size_t* to_write_p = nullptr){
        const auto& targetFormat = writer.format();
        if (targetFormat.channels > 1){
            size_t to_write;
            auto interleaved = kfr::interleave(data, to_write);
            if (to_write_p)
                *to_write_p = to_write;
            return writer.write(interleaved.get(), to_write);
        }
        else{
            if (to_write_p)
                *to_write_p = data.at(0).size();
            return writer.write(data.at(0));
        }
    }
}



#endif // KFR_ADAPT_H
