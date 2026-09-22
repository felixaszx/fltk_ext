#ifndef INCLUDE_FL_IMAGE2_HXX
#define INCLUDE_FL_IMAGE2_HXX

#include <stb/stb_image_resize2.h>
#include <FL/fl_draw.H>

#include "fl_pixbuf.hxx"

namespace fl::ext_widget
{
    class image2 : public Fl_Widget
    {
      protected:
        bool grey_scale_ = false;
        pixbuf* pixbuf_ = nullptr;

      public:
        inline constexpr image2(int x, int y, int w, int h, pixbuf* buf, const char* l = "")
            : Fl_Widget(x, y, w, h, l),
              pixbuf_(buf)
        {
        }

        inline constexpr image2(int x, int y, int w, int h, pixbuf& buf, const char* l = "")
            : image2(x, y, w, h, &buf, l)
        {
        }

        inline constexpr void //
        draw() override
        {
            if (pixbuf_ == nullptr)
            {
                fl_draw_box(box(), x(), y(), w(), h(), color());
                return;
            }

            if (w() < pixbuf_->w() || h() < pixbuf_->h())
            {
                fl_draw_box(box(), x(), y(), w(), h(), color());
                fl_rect(x(), y(), w(), h(), labelcolor());
                fl_color(labelcolor());
                fl_font(FL_COURIER, labelsize());
                fl_draw("Box too small\n[fl::image2]", x(), y(), w(), h(), FL_ALIGN_CENTER);
                return;
            }

            static auto fill_colour = [](void* data, int x, int y, int w, unsigned char* buf)
            {
                auto pixbuf = reinterpret_cast<const fl::pixbuf*>(data);
                std::memcpy(buf,                                                              //
                            pixbuf->data() + y * pixbuf->w() * pixbuf->d() + x * pixbuf->d(), //
                            pixbuf->w() * pixbuf->d());
            };

            static auto fill_mono = [](void* data, int x, int y, int w, unsigned char* buf)
            {
                auto pixbuf = reinterpret_cast<const fl::pixbuf*>(data);
                const unsigned char* begin = pixbuf->data() + y * pixbuf->w() * pixbuf->d() + x * pixbuf->d();
                for (size_t i = 0; i < pixbuf->w(); i++)
                {
                    float r = begin[i * pixbuf->d() + 0] * 0.3;
                    float g = begin[i * pixbuf->d() + 1] * 0.59;
                    float b = begin[i * pixbuf->d() + 2] * 0.11;
                    buf[i] = r + g + b;
                }
            };

            int real_x = x();
            int real_y = y();

            switch (align())
            {
                case FL_ALIGN_CENTER:
                {
                    real_x = x() + (w() - pixbuf_->w()) / 2;
                    real_y = y() + (h() - pixbuf_->h()) / 2;
                    break;
                }
                case FL_ALIGN_TOP:
                {
                    real_x = x() + (w() - pixbuf_->w()) / 2;
                    break;
                }
                case FL_ALIGN_BOTTOM:
                {
                    real_x = x() + (w() - pixbuf_->w()) / 2;
                    real_y = y() + h() - pixbuf_->h();
                    break;
                }
                case FL_ALIGN_LEFT:
                {
                    real_y = y() + (h() - pixbuf_->h()) / 2;
                    break;
                }
                case FL_ALIGN_RIGHT:
                {
                    real_x = x() + w() - pixbuf_->w();
                    real_y = y() + (h() - pixbuf_->h()) / 2;
                    break;
                }
                case FL_ALIGN_TOP_LEFT:
                {
                    break;
                }
                case FL_ALIGN_TOP_RIGHT:
                {
                    real_x = x() + w() - pixbuf_->w();
                    break;
                }
                case FL_ALIGN_BOTTOM_LEFT:
                {
                    real_y = y() + h() - pixbuf_->h();
                    break;
                }
                case FL_ALIGN_BOTTOM_RIGHT:
                {
                    real_x = x() + w() - pixbuf_->w();
                    real_y = y() + h() - pixbuf_->h();
                    break;
                }
            }

            fl_draw_box(box(), x(), y(), w(), h(), color());

            if (grey_scale_)
            {
                fl_draw_image(fill_mono, pixbuf_, real_x, real_y, //
                              pixbuf_->w(), pixbuf_->h(), 1);
            }
            else
            {
                fl_draw_image(fill_colour, pixbuf_, real_x, real_y, //
                              pixbuf_->w(), pixbuf_->h(), pixbuf_->d());
            }
        }

        inline constexpr void //
        scale(int w, int h)
        {
            if (w != pixbuf_->w() || h != pixbuf_->h())
            {
                pixbuf new_buf(w, h, pixbuf_->d());
                stbir_pixel_layout layout = STBIR_RGBA;

                if (new_buf.d() == 3)
                {
                    layout = STBIR_RGB;
                }

                auto r = stbir_resize_uint8_srgb(pixbuf_->data(), pixbuf_->w(), pixbuf_->h(), 0, //
                                                 new_buf.data(), w, h, 0,                        //
                                                 layout);

                if (r == nullptr)
                {
                    return;
                }

                *pixbuf_ = std::move(new_buf);
            }

            damage(true);
        }

        inline constexpr void //
        scale(double factor)
        {
            scale(pixbuf_->w() * factor, pixbuf_->h() * factor);
        }

        inline constexpr bool //
        grey_scale [[nodiscard]] () const
        {
            return grey_scale_;
        }

        inline constexpr void //
        grey_scale(bool on)
        {
            grey_scale_ = on;
            damage(true);
        }
    };
}; // namespace fl::ext_widget

namespace fl
{
    using image2 = fl::ext<ext_widget::image2>;
}

#endif // INCLUDE_FL_IMAGE2_HXX
