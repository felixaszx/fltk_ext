#ifndef INCLUDE_STB_HXX
#define INCLUDE_STB_HXX

#include <cstdio>
#include <vector>
#include <functional>
#include <filesystem>

namespace stb::image
{
    enum class loading_states : std::uint8_t
    {
        unpremultiply,
        iphone_png_to_rgb,
        flip_vertically,
    };

    enum class hdr_to_ldr : std::uint8_t
    {
        gama,
        scale
    };

    enum class ldr_to_hdr : std::uint8_t
    {
        gama,
        scale
    };

    void //
    set(loading_states name, bool state);

    void //
    set(hdr_to_ldr name, float value);

    void //
    set(ldr_to_hdr name, float value);

    namespace this_thread
    {
        void //
        set(loading_states name, bool state);
    }; // namespace this_thread

    struct io_callbacks
    {
        std::function<int(std::byte* data, int size)> read_ = {};
        std::function<void(int n)> skip_ = {};
        std::function<bool()> eof_ = {};
    };

    struct info
    {
        int x_;
        int y_;
        int comp_;

        inline constexpr std::size_t //
        size_bytes [[nodiscard]] () const noexcept
        {
            return x_ * y_ * comp_;
        }
    };

    std::byte*                                   //
    load [[nodiscard]] (const std::byte* buffer, //
                        int len,
                        info& info,
                        int desired_channels) noexcept;

    std::byte*                                  //
    load [[nodiscard]] (io_callbacks callbacks, //
                        info& info,
                        int desired_channels) noexcept;

    std::byte*                                                 //
    load [[nodiscard]] (const std::filesystem::path& filename, //
                        info& info,
                        int desired_channels) noexcept;

    std::byte*                        //
    load [[nodiscard]] (std::FILE* f, //
                        info& info,
                        int desired_channels) noexcept;

    std::byte*                                       //
    load_gif [[nodiscard]] (const std::byte* buffer, //
                            int len,
                            std::vector<int*>& delays,
                            info& info,
                            int& z,
                            int req_comp) noexcept;

    float*                                        //
    loadf [[nodiscard]] (const std::byte* buffer, //
                         int len,
                         info& info,
                         int desired_channels) noexcept;

    float*                                       //
    loadf [[nodiscard]] (io_callbacks callbacks, //
                         info& info,
                         int desired_channels) noexcept;

    float*                                                      //
    loadf [[nodiscard]] (const std::filesystem::path& filename, //
                         info& info,
                         int desired_channels) noexcept;

    float*                             //
    loadf [[nodiscard]] (std::FILE* f, //
                         info& info,
                         int desired_channels) noexcept;

    bool                                           //
    is_hdr [[nodiscard]] (const std::byte* buffer, //
                          int len) noexcept;

    bool //
    is_hdr [[nodiscard]] (io_callbacks callbacks) noexcept;

    bool //
    is_hdr [[nodiscard]] (const std::filesystem::path& filename) noexcept;

    bool //
    is_hdr [[nodiscard]] (std::FILE* f) noexcept;

    const char* //
    failure_reason [[nodiscard]] () noexcept;

    void //
    free(void* load_result) noexcept;

    info                                              //
    read_info [[nodiscard]] (const std::byte* buffer, //
                             int len) noexcept;

    info //
    read_info [[nodiscard]] (io_callbacks callbacks) noexcept;

    info //
    read_info [[nodiscard]] (const std::filesystem::path& filename) noexcept;

    info //
    read_info [[nodiscard]] (std::FILE* f) noexcept;
}; // namespace stb::image

#endif // INCLUDE_STB_HXX
