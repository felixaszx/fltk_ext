#ifndef INCLUDE_FL_EXT2_HXX
#define INCLUDE_FL_EXT2_HXX

#include <concepts>
#include <functional>
#include <type_traits>
#include <utility>

#include "fl_flow.hxx"
#include "fltk_headers.hxx"

namespace fl
{
    namespace theme
    {
        enum class box : std::uint8_t
        {
            win10_up = 0,
            win10_down,
            win10_hover,
            win10_frame,
            win10_text_idle,
            win10_text_active,
            win10_progress_frame,
            win10_progress_fill,
            win11_up,
            win11_down,
            win11_hover,
            win11_frame,
            win11_text_idle,
            win11_text_active,
            win11_progress_frame,
            win11_progress_fill,
            end
        };

        inline static consteval Fl_Boxtype //
        to_box_type(box b) noexcept
        {
            return static_cast<Fl_Boxtype>(FL_FREE_BOXTYPE + std::to_underlying(b));
        }

        inline static const Fl_Boxtype default_up = to_box_type(theme::box::win10_up);
        inline static const Fl_Boxtype default_down = to_box_type(theme::box::win10_down);
        inline static const Fl_Boxtype default_hover = to_box_type(theme::box::win10_hover);
        inline static const Fl_Boxtype default_frame = to_box_type(theme::box::win10_frame);
        inline static const Fl_Boxtype default_text_idle = to_box_type(theme::box::win10_text_idle);
        inline static const Fl_Boxtype default_text_active = to_box_type(theme::box::win10_text_active);
        inline static const Fl_Boxtype default_progress_frame = to_box_type(theme::box::win10_progress_frame);
        inline static const Fl_Boxtype default_progress_fill = to_box_type(theme::box::win10_progress_fill);
    }; // namespace theme

    class color
    {
      protected:
        inline static const std::int32_t color_slot = FL_FREE_COLOR + FL_NUM_FREE_COLOR - 1;

      public:
        std::uint8_t r_ = 0;
        std::uint8_t g_ = 0;
        std::uint8_t b_ = 0;
        std::uint8_t a_ = 0;

        inline constexpr color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255) noexcept
            : r_(r),
              g_(g),
              b_(b),
              a_(a) {};

        inline constexpr color(std::uint32_t hex) noexcept //
        {
            set_hex(hex);
        };

        inline constexpr operator Fl_Color() const noexcept //
        {
            return fl_rgb_color(r_, g_, b_);
        };

        inline constexpr void //
        set_hex(std::uint32_t hex) noexcept
        {
            r_ = hex / 0x10000;
            g_ = ((hex / 0x100) % 0x100);
            b_ = hex % 0x100;
        }

        inline constexpr void //
        fl_color() const noexcept
        {
            Fl::set_color(color_slot, r_, g_, b_, a_);
            ::fl_color(color_slot);
        }
    };

    inline constexpr std::size_t //
    recursive_redraw(Fl_Widget* w, std::size_t limit = 1) noexcept
    {
        Fl_Widget* p = w->parent();
        std::size_t depth = 0;
        while (p != nullptr && depth < limit)
        {
            p->redraw();
            p = p->parent();
            depth++;
        }
        return depth;
    }

    inline constexpr std::size_t //
    recursive_redraw(Fl_Widget& w, std::size_t limit = 1) noexcept
    {
        return recursive_redraw(&w, limit);
    }

    inline constexpr std::pair<int, int> //
    center_of(const Fl_Widget* w) noexcept
    {
        return {w->x() + w->w() / 2, w->y() + w->h() / 2};
    }

    inline constexpr std::pair<int, int> //
    center_of(const Fl_Widget& w) noexcept
    {
        return center_of(&w);
    }

    inline constexpr std::pair<int, int> //
    position_of(const Fl_Widget* w) noexcept
    {
        return {w->x(), w->y()};
    }

    inline constexpr std::pair<int, int> //
    position_of(const Fl_Widget& w) noexcept
    {
        return position_of(&w);
    }

    inline constexpr std::pair<int, int> //
    size_of(const Fl_Widget* w) noexcept
    {
        return {w->w(), w->h()};
    }

    inline constexpr std::pair<int, int> //
    size_of(const Fl_Widget& w) noexcept
    {
        return size_of(&w);
    }

    inline constexpr bool //
    insider_box(std::pair<int, int> point, int box_x, int box_y, int box_w, int box_h) noexcept
    {
        bool contain_x = (box_x <= point.first) && ((box_x + box_w) >= point.first);
        bool contain_y = (box_y <= point.second) && ((box_y + box_h) >= point.second);
        return contain_x && contain_y;
    }

    inline constexpr bool //
    contains_point(const Fl_Widget* w, std::pair<int, int> point) noexcept
    {
        return insider_box(point, w->x(), w->y(), w->w(), w->h());
    }

    inline constexpr bool //
    contains_point(const Fl_Widget& w, std::pair<int, int> point) noexcept
    {
        return contains_point(&w, point);
    }

    inline constexpr std::pair<int, int> //
    mouse_position() noexcept
    {
        return {Fl::event_x(), Fl::event_y()};
    }

    template <typename Wd>
        requires std::derived_from<Wd, Fl_Widget> || std::same_as<Wd, Fl_Widget>
    class ext : public Wd
    {
      protected:
        inline static void //
        callback_bridge(Fl_Widget* widget, void* func_ptr) noexcept
        {
            auto& std_func = *reinterpret_cast<std::function<void()>*>(func_ptr);
            if (std_func)
            {
                std_func();
            }
        }

      public:
        enum callback_when : std::uint8_t
        {
            always_do_callback = std::numeric_limits<std::uint8_t>::max()
        };

        std::function<void()> callback_ = {};

        void callback() const = delete;
        void user_data() const = delete;

        inline constexpr auto& //
        base(this auto&& self) noexcept
        {
            using S = decltype(self);
            using Ret = std::conditional_t<std::is_const_v<std::remove_reference_t<S>>, //
                                           const Wd*,                                   //
                                           Wd*>;
            return *reinterpret_cast<Ret>(&std::forward<S>(self));
        }

        template <typename... Args>
        inline constexpr ext(Args&&... args) noexcept
            : Wd(std::forward<Args>(args)...)
        {
            if constexpr (std::derived_from<Wd, Fl_Group>)
            {
                Wd::box(FL_FLAT_BOX);
                Wd::color(0xFFFFFFFF);

                if constexpr (!std::derived_from<Wd, Fl_Window>)
                {
                    Wd::end();
                    Wd::resizable(nullptr);
                }
                else
                {
                    Wd::resizable(this);
                }
            }

            if constexpr (!std::derived_from<Wd, Fl_Window>)
            {
                enable_ext_callback(true);
            }

            if constexpr (std::derived_from<Wd, Fl_Button>)
            {
                Wd::box(theme::default_up);
                Wd::down_box(theme::default_down);
            }

            if constexpr (std::derived_from<Wd, Fl_Input>)
            {
                Wd::box(theme::default_text_idle);
            }

            if constexpr (std::derived_from<Wd, Fl_Slider>)
            {
                Wd::box(theme::default_progress_frame);
                Wd::slider(theme::default_progress_fill);
            }
        }

        virtual ~ext() noexcept = default;

        inline constexpr void //
        enable_ext_callback(bool enabled = true) noexcept
        {
            if (enabled)
            {
                Wd::callback(callback_bridge, (void*)(&callback_));
            }
            else
            {
                Wd::callback(nullptr, nullptr);
            }
        }

        inline constexpr std::pair<int, int> //
        center [[nodiscard]] () const noexcept
        {
            return center_of(this);
        }

        inline constexpr std::size_t //
        recursive_redraw(std::size_t limit = 1) noexcept
        {
            return recursive_redraw(this, limit);
        }

        inline constexpr bool //
        contains_point [[nodiscard]] (int x, int y) const noexcept
        {
            return fl::contains_point(this, x, y);
        }

        using Wd::position;

        inline constexpr std::pair<int, int> //
        position [[nodiscard]] () const noexcept
        {
            return fl::position_of(this);
        }

        inline constexpr void //
        position(const std::pair<int, int>& new_pos) noexcept
        {
            Wd::position(new_pos.first, new_pos.second);
        }

        using Wd::size;

        inline constexpr std::pair<int, int> //
        size [[nodiscard]] () const noexcept
        {
            return fl::size_of(this);
        }

        inline constexpr void //
        size(const std::pair<int, int>& new_size) noexcept
        {
            Wd::size(new_size.first, new_size.second);
        }

        inline constexpr int //
        handle(int ev) override
        {
            // signal/slot design TBD

            // support of when(ext::always)
            if (Wd::when() == static_cast<Fl_When>(always_do_callback))
            {
                Wd::do_callback(static_cast<Fl_Callback_Reason>(always_do_callback));
            }
            return Wd::handle(ev);
        }
    };

    class enable_drag_and_move
    {
      public:
        std::uint32_t drag_threshold_ = 5;
        std::uint32_t dock_threshold_ = 0;
        bool callback_while_moving_ = false;

        inline constexpr std::pair<int, int> //
        prev_pos [[nodiscard]] () const noexcept
        {
            return prev_pos_;
        }

        virtual ~enable_drag_and_move() noexcept = default;

      protected:
        Fl_Event prev_ev_ = FL_NO_EVENT;
        std::pair<int, int> prev_mouse_ = {0, 0};
        std::pair<int, int> prev_pos_ = {0, 0};

        // perform drag and move, return true when the moving is done,
        // you should return non-zero on derived classes
        inline constexpr bool //
        drag_and_move(this auto& w, int ev) noexcept
        {
            switch (static_cast<Fl_Event>(ev))
            {
                [[unlikely]] case FL_PUSH:
                {
                    w.prev_mouse_ = mouse_position();
                    w.prev_pos_ = position_of(w);
                    return false;
                }
                case FL_DRAG:
                {
                    auto [mx, my] = mouse_position();
                    int x_off = mx - w.prev_mouse_.first;
                    int y_off = my - w.prev_mouse_.second;
                    if (w.prev_ev_ != FL_DRAG &&               //
                        std::abs(x_off) < w.drag_threshold_ && //
                        std::abs(y_off) < w.drag_threshold_)
                    {
                        return true;
                    }

                    int new_x = w.prev_pos_.first + x_off;
                    int new_y = w.prev_pos_.second + y_off;

                    // cap the positoon
                    Fl_Widget* pw = w.parent();
                    if (pw != nullptr) [[likely]]
                    {
                        int x_limit = pw->x() + pw->w() - w.w();
                        int y_limit = pw->y() + pw->h() - w.h();
                        new_x = std::clamp(new_x, pw->x(), x_limit);
                        new_y = std::clamp(new_y, pw->y(), y_limit);

                        if (std::abs(new_x - pw->x()) <= w.dock_threshold_)
                        {
                            new_x = pw->x();
                        }
                        else if (std::abs(new_x - x_limit) <= w.dock_threshold_)
                        {
                            new_x = x_limit;
                        }

                        if (std::abs(new_y - pw->y()) <= w.dock_threshold_)
                        {
                            new_y = pw->y();
                        }
                        else if (std::abs(new_y - y_limit) <= w.dock_threshold_)
                        {
                            new_y = y_limit;
                        }
                    }

                    w.position(new_x, new_y);
                    if (w.callback_while_moving_)
                    {
                        w.do_callback(FL_REASON_DRAGGED);
                    }

                    fl::recursive_redraw(w);
                    break;
                }
                default:
                {
                    break;
                }
            }

            bool moving = (w.prev_ev_ == FL_DRAG) && (ev == FL_DRAG);
            w.prev_ev_ = static_cast<Fl_Event>(ev);
            return moving;
        }
    };
}; // namespace fl

#endif // INCLUDE_FL_EXT2_HXX
