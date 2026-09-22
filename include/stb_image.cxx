#include "stb_image.hxx"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

extern "C"
{
    static int //
    io_callbacks_bridge_read(void* cb, char* data, int size) noexcept
    {
        auto func = reinterpret_cast<stb::image::io_callbacks*>(cb)->read_;
        return func(reinterpret_cast<std::byte*>(data), size);
    }

    static void //
    io_callbacks_bridge_skip(void* cb, int n) noexcept
    {
        auto func = reinterpret_cast<stb::image::io_callbacks*>(cb)->skip_;
        func(n);
    }

    static int //
    io_callbacks_bridge_eof(void* cb) noexcept
    {
        auto func = reinterpret_cast<stb::image::io_callbacks*>(cb)->eof_;
        return func();
    }
}

void //
stb::image::set(loading_states name, bool state)
{
    switch (name)
    {
        case loading_states::unpremultiply:
        {
            stbi_set_unpremultiply_on_load(state);
            break;
        }
        case loading_states::iphone_png_to_rgb:
        {
            stbi_convert_iphone_png_to_rgb(state);
            break;
        }
        case loading_states::flip_vertically:
        {
            stbi_set_flip_vertically_on_load(state);
            break;
        }
    }
}

void //
stb::image::set(hdr_to_ldr name, float value)
{
    switch (name)
    {
        case hdr_to_ldr::gama:
        {
            stbi_hdr_to_ldr_gamma(value);
            break;
        }
        case hdr_to_ldr::scale:
        {
            stbi_hdr_to_ldr_scale(value);
            break;
        }
    }
}

void //
stb::image::set(ldr_to_hdr name, float value)
{
    switch (name)
    {
        case ldr_to_hdr::gama:
        {
            stbi_ldr_to_hdr_gamma(value);
            break;
        }
        case ldr_to_hdr::scale:
        {
            stbi_ldr_to_hdr_scale(value);
            break;
        }
    }
}

void //
stb::image::this_thread::set(loading_states name, bool state)
{
    switch (name)
    {
        case loading_states::unpremultiply:
        {
            stbi_set_unpremultiply_on_load_thread(state);
            break;
        }
        case loading_states::iphone_png_to_rgb:
        {
            stbi_convert_iphone_png_to_rgb_thread(state);
            break;
        }
        case loading_states::flip_vertically:
        {
            stbi_set_flip_vertically_on_load_thread(state);
            break;
        }
    }
}

std::byte*                                //
stb::image::load(const std::byte* buffer, //
                 int len,
                 info& info,
                 int desired_channels) noexcept
{
    return reinterpret_cast<std::byte*>(                                //
        stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(buffer), //
                              len, &info.x_, &info.y_,                  //
                              &info.comp_, desired_channels));
}

std::byte*                               //
stb::image::load(io_callbacks callbacks, //
                 info& info,
                 int desired_channels) noexcept
{
    stbi_io_callbacks stb_cb = {};
    stb_cb.read = io_callbacks_bridge_read;
    stb_cb.skip = io_callbacks_bridge_skip;
    stb_cb.eof = io_callbacks_bridge_eof;
    return reinterpret_cast<std::byte*>(              //
        stbi_load_from_callbacks(&stb_cb, &callbacks, //
                                 &info.x_, &info.y_,  //
                                 &info.comp_, desired_channels));
}

std::byte*                                              //
stb::image::load(const std::filesystem::path& filename, //
                 info& info,
                 int desired_channels) noexcept
{
    std::string name_str = filename.string();
    return reinterpret_cast<std::byte*>( //
        stbi_load(name_str.c_str(),      //
                  &info.x_, &info.y_,    //
                  &info.comp_, desired_channels));
}

std::byte*                     //
stb::image::load(std::FILE* f, //
                 info& info,
                 int desired_channels) noexcept
{
    return reinterpret_cast<std::byte*>(        //
        stbi_load_from_file(f,                  //
                            &info.x_, &info.y_, //
                            &info.comp_, desired_channels));
}

std::byte*                                    //
stb::image::load_gif(const std::byte* buffer, //
                     int len,
                     std::vector<int*>& delays,
                     info& info,
                     int& z,
                     int req_comp) noexcept
{
    return reinterpret_cast<std::byte*>(                                      //
        stbi_load_gif_from_memory(reinterpret_cast<const stbi_uc*>(buffer),   //
                                  len, delays.data(), &info.x_, &info.y_, &z, //
                                  &info.comp_, req_comp));
}

float*                                     //
stb::image::loadf(const std::byte* buffer, //
                  int len,
                  info& info,
                  int desired_channels) noexcept
{
    return stbi_loadf_from_memory(reinterpret_cast<const stbi_uc*>(buffer), //
                                  len, &info.x_, &info.y_,                  //
                                  &info.comp_, desired_channels);
}

float*                                    //
stb::image::loadf(io_callbacks callbacks, //
                  info& info,
                  int desired_channels) noexcept
{
    stbi_io_callbacks stb_cb = {};
    stb_cb.read = io_callbacks_bridge_read;
    stb_cb.skip = io_callbacks_bridge_skip;
    stb_cb.eof = io_callbacks_bridge_eof;
    return stbi_loadf_from_callbacks(&stb_cb, &callbacks, //
                                     &info.x_, &info.y_,  //
                                     &info.comp_, desired_channels);
}

float*                                                   //
stb::image::loadf(const std::filesystem::path& filename, //
                  info& info,
                  int desired_channels) noexcept
{
    std::string name_str = filename.string();
    return stbi_loadf(name_str.c_str(),   //
                      &info.x_, &info.y_, //
                      &info.comp_, desired_channels);
}

float*                          //
stb::image::loadf(std::FILE* f, //
                  info& info,
                  int desired_channels) noexcept
{
    return stbi_loadf_from_file(f,                  //
                                &info.x_, &info.y_, //
                                &info.comp_, desired_channels);
}

bool //
stb::image::is_hdr(io_callbacks callbacks) noexcept
{
    stbi_io_callbacks stb_cb = {};
    stb_cb.read = io_callbacks_bridge_read;
    stb_cb.skip = io_callbacks_bridge_skip;
    stb_cb.eof = io_callbacks_bridge_eof;
    return stbi_is_hdr_from_callbacks(&stb_cb, &callbacks);
}

bool                                        //
stb::image::is_hdr(const std::byte* buffer, //
                   int len) noexcept
{
    return stbi_is_hdr_from_memory(reinterpret_cast<const stbi_uc*>(buffer), //
                                   len);
}

bool //
stb::image::is_hdr(const std::filesystem::path& filename) noexcept
{
    std::string name_str = filename.string();
    return stbi_is_hdr(name_str.c_str());
}

bool //
stb::image::is_hdr(std::FILE* f) noexcept
{
    return stbi_is_hdr_from_file(f);
}

const char* //
stb::image::failure_reason() noexcept
{
    const char* err = stbi_failure_reason();
    return err == nullptr ? "stb::image: no error" : err;
}

void //
stb::image::free(void* load_result) noexcept
{
    stbi_image_free(load_result);
}

stb::image::info                               //
stb::image::read_info(const std::byte* buffer, //
                      int len) noexcept
{
    info i = {};
    stbi_info_from_memory(reinterpret_cast<const stbi_uc*>(buffer), //
                          len, &i.x_, &i.y_, &i.comp_);
    return i;
}

stb::image::info //
stb::image::read_info [[nodiscard]] (io_callbacks callbacks) noexcept
{
    info i = {};
    stbi_io_callbacks stb_cb = {};
    stb_cb.read = io_callbacks_bridge_read;
    stb_cb.skip = io_callbacks_bridge_skip;
    stb_cb.eof = io_callbacks_bridge_eof;
    stbi_info_from_callbacks(&stb_cb, &callbacks, &i.x_, &i.y_, &i.comp_);
    return i;
}

stb::image::info //
stb::image::read_info(const std::filesystem::path& filename) noexcept
{
    info i = {};
    std::string name_str = filename.string();
    stbi_info(name_str.c_str(), &i.x_, &i.y_, &i.comp_);
    return i;
}

stb::image::info //
stb::image::read_info(std::FILE* f) noexcept
{
    info i = {};
    stbi_info_from_file(f, &i.x_, &i.y_, &i.comp_);
    return i;
}
