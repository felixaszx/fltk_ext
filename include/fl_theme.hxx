#ifndef INCLUDE_FL_THEME_HXX
#define INCLUDE_FL_THEME_HXX

#include <fltk.hxx>

namespace fl::theme
{
    namespace
    {
        inline constexpr void //
        win10_up_box_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xE1E1E1));
            fl_rect(x, y, w, h, color(0xADADAD));
        }

        inline constexpr void //
        win10_down_box_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xCCE4F7));
            fl_rect(x, y, w, h, color(0x005499));
        }

        inline constexpr void //
        win10_hover_box_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xE5F1FB));
            fl_rect(x, y, w, h, color(0x0078D7));
        }

        inline constexpr void //
        win10_frame_box_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xFFFFFF));
            fl_rect(x, y, w, h, color(0x7A7A7A));
        }

        inline constexpr void //
        win10_text_idle_box_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xFFFFFF));
            fl_rect(x, y, w, h, color(0x7A7A7A));
        }

        inline constexpr void //
        win10_text_active_box_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xFFFFFF));
            fl_rect(x, y, w, h, color(0x0078D7));
        }

        inline constexpr void //
        win10_progress_frame_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xE6E6E6));
            fl_rect(x, y, w, h, color(0xBCBCBC));
        }

        inline constexpr void //
        win10_progress_fill_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0x26A0DA));
            fl_rect(x, y, w, h, color(0xBCBCBC));
        }
    } // namespace

    namespace
    {
        inline constexpr void //
        win11_up_box_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xFDFDFD));
            fl_rect(x, y, w, h, color(0xBABABA));
        }

        inline constexpr void //
        win11_down_box_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xCCE4F7));
            fl_rect(x, y, w, h, color(0x005499));
        }

        inline constexpr void //
        win11_hover_box_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xE0EEF9));
            fl_rect(x, y, w, h, color(0x006BBE));
        }

        inline constexpr void //
        win11_frame_box_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xF9F9F9));
            fl_rect(x, y, w, h, color(0xE5E5E5));
        }

        inline constexpr void //
        win11_text_idle_box_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xF9F9F9));
            fl_rect(x, y, w, h, color(0xECECEC));
            fl_rectf(x + 3, y + h - 1, w - 6, 1, color(0x838383));
        }

        inline constexpr void //
        win11_text_active_box_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xF9F9F9));
            fl_rect(x, y, w, h, color(0xECECEC));
            fl_rectf(x + 3, y + h - 2, w - 6, 2, color(0x0067C0));
        }

        inline constexpr void //
        win11_progress_frame_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0xE6E6E6));
            fl_rect(x, y, w, h, color(0xBCBCBC));
        }

        inline constexpr void //
        win11_progress_fill_draw(int x, int y, int w, int h, Fl_Color c) noexcept
        {
            fl_rectf(x, y, w, h, color(0x0070CB));
            fl_rect(x, y, w, h, color(0xBCBCBC));
        }
    } // namespace

    inline constexpr Fl_Boxtype //
    box_type [[nodiscard]] (box index) noexcept
    {
        return static_cast<Fl_Boxtype>(FL_FREE_BOXTYPE + std::to_underlying(index));
    }

    inline constexpr void //
    init() noexcept
    {
        static auto box_i = [](std::uint32_t index) { return static_cast<Fl_Boxtype>(FL_FREE_BOXTYPE + index); };
        static void (*draw_funcs[])(int, int, int, int, Fl_Color) = {
            win10_up_box_draw,         win10_down_box_draw,      win10_hover_box_draw,       //
            win10_frame_box_draw,      win10_text_idle_box_draw, win10_text_active_box_draw, //
            win10_progress_frame_draw, win10_progress_fill_draw,                             //
            win11_up_box_draw,         win11_down_box_draw,      win11_hover_box_draw,       //
            win11_frame_box_draw,      win11_text_idle_box_draw, win11_text_active_box_draw, //
            win11_progress_frame_draw, win11_progress_fill_draw,
        };

        for (std::uint32_t i = 0; i < std::to_underlying(box::end); i++)
        {
            fl::sys::set_boxtype(box_i(i), draw_funcs[i], 0, 0, 0, 0);
        }

        for (std::size_t s = 0; s < fl::sys::screen_count(); s++)
        {
            fl::sys::screen_scale(s, 1);
        }

        fl::sys::visible_focus(false);
        fl::sys::visual(FL_RGB8);
        fl::sys::gl_visual(FL_RGB8);
    }
}; // namespace fl::theme

#endif // INCLUDE_FL_THEME_HXX
