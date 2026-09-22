#ifndef INCLUDE_FL_PIXBUF_HXX
#define INCLUDE_FL_PIXBUF_HXX

#include <memory>
#include <cstring>
#include <span>

#include "fl_ext.hxx"

namespace fl
{
    class pixbuf
    {
      protected:
        uint32_t w_ = 0;
        uint32_t h_ = 0;
        uint32_t d_ = 0;
        std::unique_ptr<unsigned char, //
                        decltype([](void* p) { std::free(p); })>
            pixels_ = {};

      public:
        inline constexpr pixbuf(uint32_t w, uint32_t h, uint32_t d);

        inline constexpr uint32_t //
        w [[nodiscard]] () const noexcept;

        inline constexpr uint32_t //
        h [[nodiscard]] () const noexcept;

        inline constexpr uint32_t //
        d [[nodiscard]] () const noexcept;

        inline constexpr size_t //
        size_bytes [[nodiscard]] () const noexcept;

        inline constexpr void //
        write(void* from) noexcept;

        inline constexpr std::vector<unsigned char> //
        read [[nodiscard]] () const;

        inline constexpr auto //
        at(this auto&& self, uint32_t x, uint32_t y) noexcept;

        inline constexpr auto //
        operator[](this auto&& self, uint32_t x, uint32_t y) noexcept;

        inline constexpr void //
        resize(uint32_t new_w, uint32_t new_h);

        constexpr auto //
        data(this auto&& self);
    };
}; // namespace fl

//
//
//
// Implementations
//
//
//

inline constexpr fl::pixbuf::pixbuf(uint32_t w, uint32_t h, uint32_t d)
    : w_(w),
      h_(h),
      d_(d)
{
    if (d != 3 && d != 4)
    {
        return;
    }

    pixels_.reset(reinterpret_cast<unsigned char*>(std::calloc(w * h * d, sizeof(unsigned char))));
}

inline constexpr uint32_t //
fl::pixbuf::w [[nodiscard]] () const noexcept
{
    return w_;
}

inline constexpr uint32_t //
fl::pixbuf::h [[nodiscard]] () const noexcept
{
    return h_;
}

inline constexpr uint32_t //
fl::pixbuf::d [[nodiscard]] () const noexcept
{
    return d_;
}

inline constexpr size_t //
fl::pixbuf::size_bytes [[nodiscard]] () const noexcept
{
    return w_ * h_ * d_;
}

inline constexpr void //
fl::pixbuf::write(void* from) noexcept
{
    std::memcpy(pixels_.get(), from, size_bytes());
}

inline constexpr std::vector<unsigned char> //
fl::pixbuf::read [[nodiscard]] () const
{
    std::vector<unsigned char> tmp(size_bytes());
    std::memcpy(tmp.data(), pixels_.get(), size_bytes());
    return tmp;
}

inline constexpr auto //
fl::pixbuf::at(this auto&& self, uint32_t x, uint32_t y) noexcept
{
    auto pos = self.pixels_.get() + y * self.w_ * self.d_ + x * self.d_;
    if constexpr (std::is_const_v<std::remove_reference_t<decltype(self)>>)
    {
        return std::span<const unsigned char>(pos, self.d_);
    }
    else
    {
        return std::span<unsigned char>(pos, self.d_);
    }
}

inline constexpr auto //
fl::pixbuf::operator[](this auto&& self, uint32_t x, uint32_t y) noexcept
{
    return std::forward<decltype(self)>(self).at(x, y);
}

inline constexpr void //
fl::pixbuf::resize(uint32_t new_w, uint32_t new_h)
{
    if (new_w > w_ && new_h > h_)
    {
        pixels_.reset(
            reinterpret_cast<unsigned char*>(std::realloc(pixels_.release(), w_ * h_ * d_ * sizeof(unsigned char))));
    }
}

inline constexpr auto //
fl::pixbuf::data(this auto&& self)
{
    if constexpr (std::is_const_v<std::remove_reference_t<decltype(self)>>)
    {
        return reinterpret_cast<const unsigned char*>(self.pixels_.get());
    }
    else
    {
        return reinterpret_cast<unsigned char*>(self.pixels_.get());
    }
}

#endif // INCLUDE_FL_PIXBUF_HXX
