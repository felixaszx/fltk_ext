#ifndef INCLUDE_SNDFILE_HXX
#define INCLUDE_SNDFILE_HXX

#include <vector>
#include <format>
#include <filesystem>

#include <sndfile.h>

namespace sf
{
    struct format
    {
        enum major
        {
            wav = SF_FORMAT_WAV,
            aiff = SF_FORMAT_AIFF,
            au = SF_FORMAT_AU,
            raw = SF_FORMAT_RAW,
            paf = SF_FORMAT_PAF,
            svx = SF_FORMAT_SVX,
            nist = SF_FORMAT_NIST,
            voc = SF_FORMAT_VOC,
            ircam = SF_FORMAT_IRCAM,
            w64 = SF_FORMAT_W64,
            mat4 = SF_FORMAT_MAT4,
            mat5 = SF_FORMAT_MAT5,
            pvf = SF_FORMAT_PVF,
            xi = SF_FORMAT_XI,
            htk = SF_FORMAT_HTK,
            sds = SF_FORMAT_SDS,
            avr = SF_FORMAT_AVR,
            wavex = SF_FORMAT_WAVEX,
            sd2 = SF_FORMAT_SD2,
            flac = SF_FORMAT_FLAC,
            caf = SF_FORMAT_CAF,
            wve = SF_FORMAT_WVE,
            ogg = SF_FORMAT_OGG,
            mpc2k = SF_FORMAT_MPC2K,
            rf64 = SF_FORMAT_RF64,
            mpeg = SF_FORMAT_MPEG
        };

        inline constexpr static const std::string_view //
        to_string(major m) noexcept;

        enum sub : std::uint8_t
        {
            pcm_i8 = SF_FORMAT_PCM_S8,
            pcm_i16 = SF_FORMAT_PCM_16,
            pcm_i24 = SF_FORMAT_PCM_24,
            pcm_i32 = SF_FORMAT_PCM_32,
            pcm_u8 = SF_FORMAT_PCM_U8,
            pcm_f32 = SF_FORMAT_FLOAT,
            pcm_f64 = SF_FORMAT_DOUBLE,
            ulaw = SF_FORMAT_ULAW,
            alaw = SF_FORMAT_ALAW,
            ima_adpcm = SF_FORMAT_IMA_ADPCM,
            ms_adpcm = SF_FORMAT_MS_ADPCM,
            gsm610 = SF_FORMAT_GSM610,
            vox_adpcm = SF_FORMAT_VOX_ADPCM,
            nms_adpcm_16 = SF_FORMAT_NMS_ADPCM_16,
            nms_adpcm_24 = SF_FORMAT_NMS_ADPCM_24,
            nms_adpcm_32 = SF_FORMAT_NMS_ADPCM_32,
            g721_32 = SF_FORMAT_G721_32,
            g723_24 = SF_FORMAT_G723_24,
            g723_40 = SF_FORMAT_G723_40,
            dwvw_12 = SF_FORMAT_DWVW_12,
            dwvw_16 = SF_FORMAT_DWVW_16,
            dwvw_24 = SF_FORMAT_DWVW_24,
            dwvw_n = SF_FORMAT_DWVW_N,
            dpcm_8 = SF_FORMAT_DPCM_8,
            dpcm_16 = SF_FORMAT_DPCM_16,
            vorbis = SF_FORMAT_VORBIS,
            opus = SF_FORMAT_OPUS,
            alac_16 = SF_FORMAT_ALAC_16,
            alac_20 = SF_FORMAT_ALAC_20,
            alac_24 = SF_FORMAT_ALAC_24,
            alac_32 = SF_FORMAT_ALAC_32,
            mpeg_layer1 = SF_FORMAT_MPEG_LAYER_I,
            mpeg_layer2 = SF_FORMAT_MPEG_LAYER_II,
            mpeg2_layer3 = SF_FORMAT_MPEG_LAYER_III
        };

        enum endianess
        {
            auto_endian = SF_ENDIAN_FILE,
            little_endian = SF_ENDIAN_LITTLE,
            big_endian = SF_ENDIAN_BIG,
            hardware_endian = SF_ENDIAN_CPU
        };
    };

    struct metadata
    {
        enum flags : std::uint8_t
        {
            title = SF_STR_TITLE,
            copyright = SF_STR_COPYRIGHT,
            software = SF_STR_SOFTWARE,
            artist = SF_STR_ARTIST,
            comments = SF_STR_COMMENT,
            data = SF_STR_DATE,
            album = SF_STR_ALBUM,
            license = SF_STR_LICENSE,
            track_number = SF_STR_TRACKNUMBER,
            genre = SF_STR_GENRE
        };
    };

    constexpr const std::string_view //
    get_library_version() noexcept;

    class file
    {
      protected:
        SNDFILE* sndfile_ = nullptr;
        SF_INFO info_ = {};

      public:
        inline constexpr file() noexcept = default;
        inline constexpr file(const file& from) = delete;
        inline constexpr file& operator=(const file& from) = delete;
        inline constexpr file(file&& from) noexcept;
        inline constexpr file& operator=(file&& from) noexcept;
        inline constexpr file(const std::filesystem::path& file_path, std::ios::openmode mode = std::ios::in);

        inline constexpr ~file() noexcept;

        inline constexpr std::size_t //
        frame_size [[nodiscard]] () const noexcept;

        inline constexpr std::size_t //
        sample_rate [[nodiscard]] () const noexcept;

        inline constexpr std::size_t //
        channels [[nodiscard]] () const noexcept;

        inline constexpr format::major //
        format [[nodiscard]] () const noexcept;

        inline constexpr format::sub //
        sub_type [[nodiscard]] () const noexcept;

        inline constexpr format::endianess //
        endianess [[nodiscard]] () const noexcept;

        inline constexpr std::size_t //
        sections [[nodiscard]] () const noexcept;

        inline constexpr bool //
        seekable [[nodiscard]] () const noexcept;

        inline constexpr std::size_t //
        bitrate [[nodiscard]] () const noexcept;

        inline constexpr bool //
        valid [[nodiscard]] () const noexcept;

        inline constexpr void //
        seekg(std::ptrdiff_t frame, std::ios::seekdir at = std::ios::seekdir::cur) const;

        inline constexpr std::size_t //
        tellg [[nodiscard]] () const noexcept;

        inline constexpr void //
        open(const std::filesystem::path& file_path, std::ios::openmode mode = std::ios::in);

        inline constexpr void //
        close() noexcept;

        template <typename R>
        inline constexpr std::size_t //
        read(R* to, std::size_t frame_count) const noexcept;

        template <typename R>
        inline constexpr std::vector<R> //
        read [[nodiscard]] (std::size_t frame_count) const noexcept;

        template <typename R>
        inline constexpr std::size_t //
        write(const R* frames, std::size_t frame_count) noexcept;

        template <typename R>
        inline constexpr std::size_t //
        write(const std::vector<R>& frames) noexcept;

        inline constexpr void //
        flush() noexcept;

        inline constexpr const std::string_view //
        get_metadata [[nodiscard]] (metadata::flags type) const noexcept;

        inline constexpr bool //
        set_metadata [[nodiscard]] (metadata::flags type, const std::string& str);
    };
}; // namespace sf

//
//
//
// Implementations
//
//
//

inline constexpr const std::string_view //
sf::get_library_version() noexcept
{
    return sf_version_string();
}

inline constexpr const std::string_view //
sf::format::to_string(major m) noexcept
{
    switch (m)
    {
        case wav:
            return "wav";
        case aiff:
            return "aiff";
        case au:
            return "au";
        case raw:
            return "raw";
        case paf:
            return "paf";
        case svx:
            return "svx";
        case nist:
            return "nist";
        case voc:
            return "voc";
        case ircam:
            return "ircam";
        case w64:
            return "w64";
        case mat4:
            return "mat4";
        case mat5:
            return "mat5";
        case pvf:
            return "pvf";
        case xi:
            return "xi";
        case htk:
            return "htk";
        case sds:
            return "sds";
        case avr:
            return "avr";
        case wavex:
            return "wavex";
        case sd2:
            return "sd2";
        case flac:
            return "flac";
        case caf:
            return "caf";
        case wve:
            return "wve";
        case ogg:
            return "ogg";
        case mpc2k:
            return "mpc2k";
        case rf64:
            return "rf64";
        case mpeg:
            return "mpeg";
    }
}

inline constexpr sf::file::file(file&& from) noexcept
{
    this->operator=(std::move(from));
}

inline constexpr sf::file& sf::file::operator=(file&& from) noexcept
{
    sndfile_ = from.sndfile_;
    info_ = from.info_;
    from.sndfile_ = nullptr;
    from.info_ = {};
    return *this;
}

inline constexpr sf::file::file(const std::filesystem::path& file_path, std::ios::openmode mode)
{
    open(file_path, mode);
}

inline constexpr sf::file::~file() noexcept //
{
    close();
}

inline constexpr std::size_t //
sf::file::frame_size [[nodiscard]] () const noexcept
{
    return info_.frames;
}

inline constexpr std::size_t //
sf::file::sample_rate [[nodiscard]] () const noexcept
{
    return info_.samplerate;
}

inline constexpr std::size_t //
sf::file::channels [[nodiscard]] () const noexcept
{
    return info_.channels;
}

inline constexpr sf::format::major //
sf::file::format [[nodiscard]] () const noexcept
{
    return static_cast<format::major>(info_.format & SF_FORMAT_TYPEMASK);
}

inline constexpr sf::format::sub //
sf::file::sub_type [[nodiscard]] () const noexcept
{
    return static_cast<format::sub>(info_.format & SF_FORMAT_SUBMASK);
}

inline constexpr sf::format::endianess //
sf::file::endianess [[nodiscard]] () const noexcept
{
    return static_cast<format::endianess>(info_.format & SF_FORMAT_ENDMASK);
}

inline constexpr std::size_t //
sf::file::sections [[nodiscard]] () const noexcept
{
    return info_.sections;
}

inline constexpr bool //
sf::file::seekable [[nodiscard]] () const noexcept
{
    return info_.seekable;
}

inline constexpr std::size_t //
sf::file::bitrate [[nodiscard]] () const noexcept
{
    return sf_current_byterate(sndfile_) * 8;
}

inline constexpr bool //
sf::file::valid [[nodiscard]] () const noexcept
{
    return sndfile_ != nullptr;
}

inline constexpr void //
sf::file::seekg(std::ptrdiff_t frame, std::ios::seekdir at) const
{
    static auto get_sf_seek = [](std::ios::seekdir w)
    {
        switch (w)
        {
            case std::ios_base::beg:
                return SF_SEEK_SET;
            case std::ios_base::cur:
                return SF_SEEK_CUR;
            case std::ios_base::end:
                return SF_SEEK_END;
        }
    };

    if (sf_seek(sndfile_, frame, get_sf_seek(at)) == -1)
    {
#if defined(__cpp_exceptions) || defined(_CPPUNWIND)
        throw std::runtime_error("sf::sf::file::seek(...) beyond the range.");
#endif
    }
}

inline constexpr std::size_t //
sf::file::tellg [[nodiscard]] () const noexcept
{
    return sf_seek(sndfile_, 0, SF_SEEK_CUR);
}

inline constexpr void //
sf::file::open(const std::filesystem::path& file_path, std::ios::openmode mode)
{
    static auto get_integer_mode = [](std::ios::openmode std_mode)
    {
        switch (std_mode)
        {
            case std::ios::in:
            {
                return SFM_READ;
            }
            case std::ios::out:
            {
                return SFM_WRITE;
            }
            case std::ios::in | std::ios::out:
            {
                return SFM_RDWR;
            }
            default:
            {
                return SF_FALSE;
            }
        }
    };

    if (!valid())
    {

        if (std::filesystem::exists(file_path))
        {
#if defined(_WIN64)
            sndfile_ = sf_wchar_open(file_path.c_str(), get_integer_mode(mode), &info_);
#else
            sndfile_ = sf_open(file_path.c_str(), get_integer_mode(mode), &info_);
#endif

#if defined(__cpp_exceptions) || defined(_CPPUNWIND)
            if (sndfile_ == nullptr)
            {
                throw std::runtime_error(std::format("Fail to open file {}", file_path.string()));
            }
#endif
        }
    }
}

inline constexpr void //
sf::file::close() noexcept
{
    if (sndfile_)
    {
        sf_close(sndfile_);
        sndfile_ = nullptr;
        info_ = {};
    }
}

template <typename R>
inline constexpr std::size_t //
sf::file::read(R* to, std::size_t frame_count) const noexcept
{
    std::size_t actual_read = 0;
    if constexpr (std::same_as<float, R>)
    {
        actual_read = sf_readf_float(sndfile_, to, frame_count);
    }
    else if constexpr (std::same_as<double, R>)
    {
        actual_read = sf_readf_double(sndfile_, to, frame_count);
    }
    else if constexpr (std::same_as<short, R>)
    {
        actual_read = sf_readf_short(sndfile_, to, frame_count);
    }
    else if constexpr (std::same_as<int, R>)
    {
        actual_read = sf_readf_int(sndfile_, to, frame_count);
    }
    else
    {
        return 0;
    }
    return actual_read;
}

template <typename R>
inline constexpr std::vector<R> //
sf::file::read [[nodiscard]] (std::size_t frame_count) const noexcept
{
    std::vector<R> buf(frame_count * channels());
    std::size_t actual_read = read<R>(buf.data(), frame_count);
    if (actual_read == 0)
    {
        return {};
    }

    buf.resize(actual_read);
    return buf;
}

template <typename R>
inline constexpr std::size_t //
sf::file::write(const R* frames, std::size_t frame_count) noexcept
{
    if constexpr (std::same_as<float, R>)
    {
        return sf_writef_float(sndfile_, frames, frame_count);
    }
    else if constexpr (std::same_as<double, R>)
    {
        return sf_writef_double(sndfile_, frames, frame_count);
    }
    else if constexpr (std::same_as<short, R>)
    {
        return sf_writef_short(sndfile_, frames, frame_count);
    }
    else if constexpr (std::same_as<int, R>)
    {
        return sf_writef_int(sndfile_, frames, frame_count);
    }
    else
    {
        return 0;
    }
}

template <typename R>
inline constexpr std::size_t //
sf::file::write(const std::vector<R>& frames) noexcept
{
    return write(frames.data(), frames.size());
}

inline constexpr void //
sf::file::flush() noexcept
{
    sf_write_sync(sndfile_);
}

inline constexpr const std::string_view //
sf::file::get_metadata [[nodiscard]] (metadata::flags type) const noexcept
{
    return sf_get_string(sndfile_, type);
}

inline constexpr bool //
sf::file::set_metadata [[nodiscard]] (metadata::flags type, const std::string& str)
{
    int ret = sf_set_string(sndfile_, type, str.c_str());
    if (ret != 0)
    {
#if defined(__cpp_exceptions) || defined(_CPPUNWIND)
        throw std::runtime_error(sf_error_number(ret));
#else
        return false;
#endif
    }
    return true;
}

#endif // INCLUDE_SNDFILE_HXX
