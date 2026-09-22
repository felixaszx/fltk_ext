#include "std_extention.hxx"
#include <print>

#include "fltk.hxx"
#include "fl_theme.hxx"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "fl_image2.hxx"
#include "stb_image.hxx"
#include "stb_image.cxx"

int main(int argc, char** argv)
{
    fl::theme::init();
    fl::double_window window(800, 600);
    fl::flow user_space(0, 0, window.w(), window.h());
    fl::button sw(0, 0, 50, 50);
    user_space.rule(sw, "=<^");

    stb::image::info eula_info = {};
    std::byte* eula_pixbuf = stb::image::load("eula.png", eula_info, 4);
    fl::pixbuf buf(eula_info.x_, eula_info.y_, eula_info.comp_);
    std::memcpy(buf.data(), eula_pixbuf, eula_info.size_bytes());
    fl::image2 aaa(0, 0, 1, 1, buf);
    aaa.scale(1920, 1080);
    aaa.grey_scale(true);

    window.add(user_space);
    window.show();

    user_space.rule(aaa, "=<=^");

    sw.callback_ = [&]() { aaa.grey_scale(!aaa.grey_scale()); };

    while (fl::sys::check())
    {
        std::this_thread::sleep_for(8ms);
    }

    return 0;
}
