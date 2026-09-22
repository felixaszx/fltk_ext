/**
 * @file std_extention.hxx
 * @author Felixaszx (felixaszx@outlook.com)
 * @brief Core defines and help tempaltes
 * @version 0.1
 * @date 2025-07-12
 *
 * @copyright MIT License Copyright (c) 2025
 *
 */

#ifndef STD_EXTENTION_HXX
#define STD_EXTENTION_HXX

#include <span>
#include <atomic>
#include <chrono>
#include <memory>
#include <thread>
#include <ranges>
#include <iostream>
#include <type_traits>
#include <source_location>

#define STD_EXT_HPP_NAMESPACE std_ext

namespace STD_EXT_HPP_NAMESPACE::i_ // internal namespace
{
    template <typename... F>
    struct overload_call_t : F...
    {
        using F::operator()...;
    };

    template <typename L>
    struct limit_v_t
    {
        template <typename M>
        inline static const M as = L::template as<M>;
    };

    template <typename M, typename L>
    inline constexpr bool //
    operator<(const M& x, const limit_v_t<L>& y)
    {
        return x < limit_v_t<L>::template as<M>;
    }

    template <typename M, typename L>
    inline constexpr bool //
    operator<=(const M& x, const limit_v_t<L>& y)
    {
        return x <= limit_v_t<L>::template as<M>;
    }

    template <typename M, typename L>
    inline constexpr bool //
    operator>(const M& x, const limit_v_t<L>& y)
    {
        return x > limit_v_t<L>::template as<M>;
    }

    template <typename M, typename L>
    inline constexpr bool //
    operator>=(const M& x, const limit_v_t<L>& y)
    {
        return x >= limit_v_t<L>::template as<M>;
    }

    template <typename M, typename L>
    inline constexpr bool //
    operator==(const M& x, const limit_v_t<L>& y)
    {
        return x == limit_v_t<L>::template as<M>;
    }

    template <bool S = false>
    struct max_v_t : public limit_v_t<max_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::max();
            }
            else
            {
                return std::numeric_limits<M>::max();
            }
        }

        inline consteval const max_v_t<!S> //
        operator-() const
        {
            return max_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::max();
    };

    template <bool S = false>
    struct min_v_t : public limit_v_t<min_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::min();
            }
            else
            {
                return std::numeric_limits<M>::min();
            }
        }

        inline consteval const min_v_t<!S> //
        operator-() const
        {
            return min_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::min();
    };

    template <bool S = false>
    struct inf_v_t : public limit_v_t<inf_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::infinity();
            }
            else
            {
                return std::numeric_limits<M>::infinity();
            }
        }

        inline consteval const inf_v_t<!S> //
        operator-() const
        {
            return inf_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::infinity();
    };

    template <bool S = false>
    struct epsilon_v_t : public limit_v_t<epsilon_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::epsilon();
            }
            else
            {
                return std::numeric_limits<M>::epsilon();
            }
        }

        inline consteval const epsilon_v_t<!S> //
        operator-() const
        {
            return epsilon_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::epsilon();
    };

    template <bool S = false>
    struct lowest_v_t : public limit_v_t<lowest_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::lowest();
            }
            else
            {
                return std::numeric_limits<M>::lowest();
            }
        }

        inline consteval const lowest_v_t<!S> //
        operator-() const
        {
            return lowest_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::lowest();
    };

    struct quiet_NaN_v_t : public limit_v_t<quiet_NaN_v_t>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            return std::numeric_limits<M>::quiet_NaN();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::quiet_NaN();
    };

    struct sig_NaN_v_t : public limit_v_t<sig_NaN_v_t>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            return std::numeric_limits<M>::signaling_NaN();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::signaling_NaN();
    };

    template <bool S = false>
    struct round_error_v_t : public limit_v_t<round_error_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::round_error();
            }
            else
            {
                return std::numeric_limits<M>::round_error();
            }
        }

        inline consteval const round_error_v_t<!S> //
        operator-() const
        {
            return round_error_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::round_error();
    };

    template <bool S = false>
    struct denorm_min_v_t : public limit_v_t<denorm_min_v_t<S>>
    {
        template <typename M>
        inline consteval //
        operator M() const
        {
            if constexpr (S)
            {
                return -std::numeric_limits<M>::denorm_min();
            }
            else
            {
                return std::numeric_limits<M>::denorm_min();
            }
        }

        inline consteval const denorm_min_v_t<!S> //
        operator-() const
        {
            return denorm_min_v_t<!S>();
        }

        template <typename M>
        inline static const M as = std::numeric_limits<M>::denorm_min();
    };
}; // namespace STD_EXT_HPP_NAMESPACE::i_

namespace STD_EXT_HPP_NAMESPACE
{
    using i8 = std::int8_t;
    using u8 = std::uint8_t;
    using i16 = std::int16_t;
    using u16 = std::uint16_t;
    using i32 = std::int32_t;
    using u32 = std::uint32_t;
    using i64 = std::int64_t;
    using u64 = std::uint64_t;
    using imax = std::intmax_t;
    using umax = std::uintmax_t;
    using usz = std::size_t;
    using ssz = std::ptrdiff_t;
    using ptrdiff = std::ptrdiff_t;
    using uptr = std::uintptr_t;
    using iptr = std::intptr_t;

    using uchar = unsigned char;
    using char8 = char8_t;
    using char16 = char16_t;
    using char32 = char32_t;
    using wchar = wchar_t;

    using f32 = float;
    using f64 = double;
    using flong = long double;

    inline static const i_::quiet_NaN_v_t quiet_NaN = {};
    inline static const i_::sig_NaN_v_t sig_NaN = {};
    inline static const i_::quiet_NaN_v_t nan_v = {};

    inline static const i_::min_v_t min_v = {};
    inline static const i_::lowest_v_t lowest_v = {};
    inline static const i_::max_v_t max_v = {};
    inline static const i_::epsilon_v_t epsilon_v = {};
    inline static const i_::round_error_v_t round_err_v = {};
    inline static const i_::inf_v_t inf_v = {};
    inline static const i_::denorm_min_v_t denorm_min_v = {};

    // atomic variants
    using atomic_bool = std::atomic<bool>;
    using atomic_i8 = std::atomic<i8>;
    using atomic_u8 = std::atomic<u8>;
    using atomic_i16 = std::atomic<i16>;
    using atomic_u16 = std::atomic<u16>;
    using atomic_i32 = std::atomic<i32>;
    using atomic_u32 = std::atomic<u32>;
    using atomic_i64 = std::atomic<i64>;
    using atomic_u64 = std::atomic<u64>;
    using atomic_imax = std::atomic<imax>;
    using atomic_umax = std::atomic<umax>;
    using atomic_usz = std::atomic<usz>;
    using atomic_ssz = std::atomic<ssz>;
    using atomic_ptrdiff = std::atomic<ptrdiff>;
    using atomic_uptr = std::atomic<uptr>;
    using atomic_iptr = std::atomic<iptr>;

    using atomic_char = std::atomic<char>;
    using atomic_uchar = std::atomic<uchar>;
    using atomic_char8 = std::atomic<char8>;
    using atomic_char16 = std::atomic<char16>;
    using atomic_char32 = std::atomic<char32>;
    using atomic_wchar = std::atomic<wchar>;

    using atomic_f32 = std::atomic<f32>;
    using atomic_f64 = std::atomic<f64>;
    using atomic_flag = std::atomic_flag;

    template <typename T>
    using atomic = std::atomic<T>;

    template <std::size_t N>
    struct ts_idx_string_literal
    {
        char str_[N];
        consteval ts_idx_string_literal(const char (&str)[N]) { std::copy_n(str, N, str_); }
    };

    template <std::unsigned_integral Idx = std::size_t, ts_idx_string_literal Name = "", std::size_t Class = 0>
    struct ts_idx
    {
      public:
        inline static const ts_idx zero = static_cast<Idx>(0ull);
        inline static const ts_idx null = std::bit_cast<Idx>(~static_cast<Idx>(0ull));

      protected:
        Idx idx_;

      public:
        inline constexpr operator bool() const noexcept { return valid(); }
        inline constexpr bool operator==(const ts_idx& x) const noexcept { return idx_ == x.idx_; }
        inline constexpr bool operator<=(const ts_idx& x) const noexcept { return idx_ <= x.idx_; }
        inline constexpr bool operator>=(const ts_idx& x) const noexcept { return idx_ >= x.idx_; }
        inline constexpr bool operator<(const ts_idx& x) const noexcept { return idx_ < x.idx_; }
        inline constexpr bool operator>(const ts_idx& x) const noexcept { return idx_ > x.idx_; }
        inline constexpr ts_idx(Idx i = ts_idx::null) noexcept { idx_ = i; }

        inline constexpr const Idx //
        number [[nodiscard]] () const noexcept
        {
            return idx_;
        };

        inline constexpr const bool //
        valid [[nodiscard]] () const noexcept
        {
            return null.idx_ != idx_;
        };

        inline constexpr const ts_idx //
        off_by [[nodiscard]] (long long off) const noexcept
        {
            return *this ? ts_idx(idx_ + off) : null;
        };

        template <std::integral I>
        inline constexpr //
        operator I() const noexcept
        {
            return idx_;
        }

        template <std::integral I>
        inline constexpr bool //
        operator==(const I& x) const noexcept
        {
            return idx_ == x;
        }

        template <std::integral I>
        inline constexpr bool //
        operator<=(const I& x) const noexcept
        {
            return idx_ <= x;
        }

        template <std::integral I>
        inline constexpr bool //
        operator>=(const I& x) const noexcept
        {
            return idx_ >= x;
        }

        template <std::integral I>
        inline constexpr bool //
        operator<(const I& x) const noexcept
        {
            return idx_ < x;
        }

        template <std::integral I>
        inline constexpr bool //
        operator>(const I& x) const noexcept
        {
            return idx_ > x;
        }
    };

    enum struct cmp_result : signed char
    {
        less = -1,
        equivalent = 0,
        greater = 1
    };

    template <typename T>
        requires(std::same_as<T, std::strong_ordering> || //
                 std::same_as<T, std::weak_ordering> ||   //
                 std::same_as<T, std::partial_ordering>)
    constexpr cmp_result //
    cmp_to_integral(T x) noexcept
    {
        return std::bit_cast<cmp_result>(x);
    }
}; // namespace STD_EXT_HPP_NAMESPACE

namespace STD_EXT_HPP_NAMESPACE
{
    template <typename T>
    inline constexpr auto //
    aligned [[nodiscard]] (const T& size, std::size_t alignment = 16) noexcept
        requires std::is_arithmetic_v<T>
    {
        return alignment * ((size - 1) / alignment) + alignment;
    }

    template <typename A>
    inline consteval std::size_t //
    lengthof(A&& c_arr) noexcept
        requires(std::is_bounded_array_v<std::remove_cvref_t<A>>)
    {
        return sizeof(c_arr) / sizeof(c_arr[0]);
    }

    template <typename T>
    inline consteval std::size_t //
    widthof(T&& obj) noexcept
    {
        return sizeof(obj) * CHAR_BIT;
    }

    inline constexpr auto //
    stl_expand(auto&& stl_container, std::size_t extra)
    {
        return stl_container.resize(stl_container.size() + extra);
    }

    inline constexpr auto //
    stl_reserve_more(auto&& stl_container, std::size_t extra)
    {
        return stl_container.reserve(stl_container.size() + extra);
    }

    inline constexpr auto //
    stl_swap_clear(auto&& stl_container)
    {
        return std::remove_cvref_t<decltype(stl_container)>().swap(stl_container);
    }

    inline constexpr auto //
    stl_sizeof(auto&& stl_container)
    {
        return stl_container.size() * sizeof(decltype(stl_container)::value_type);
    }

    using c_delete = decltype([](void* p) { std::free(p); });

    struct c_new
    {
      private:
        const std::size_t count_ = 0;

      public:
        inline constexpr c_new(std::size_t count) noexcept
            : count_(count)
        {
        }

        template <typename P>
            requires std::is_pointer_v<std::remove_cvref_t<P>>
        inline constexpr operator P() const noexcept
        {
            if constexpr (std::same_as<void, std::remove_cvref_t<std::remove_pointer_t<P>>>)
            {
                return nullptr;
            }
            else
            {
                const std::size_t size = sizeof(std::remove_cvref_t<std::remove_pointer_t<P>>);
                return count_ == 0 ? nullptr : reinterpret_cast<P>(std::calloc(count_, size));
            }
        }
    };

    template <typename Tp, typename Dp = std::default_delete<Tp>>
    using unique = std::unique_ptr<Tp, Dp>;

    template <typename Tp>
    using shared = std::shared_ptr<Tp>;

    template <typename Tp>
    using weak = std::weak_ptr<Tp>;

    // This outperform libc++'s std::mutex (~2M /s) on Windows 10/11, max at 16 thread Ryzen 7700X, 64M-718M /s
    struct spinlock
    {
      protected:
        atomic_flag m_ = false;

      public:
        inline constexpr bool //
        try_lock [[nodiscard]] () noexcept
        {
            return !(m_.test(std::memory_order_relaxed) || //
                     m_.test_and_set(std::memory_order_acquire));
        }

        inline constexpr void //
        lock(std::size_t spin_before_sleep = 16) noexcept
        {
            using namespace std::chrono_literals;
            for (std::size_t spins = 0; !try_lock(); spins++)
            {
                if (spins == spin_before_sleep)
                {
                    spins = 0;
                    std::this_thread::sleep_for(1ns);
                }
            }
        }

        inline constexpr void //
        unlock() noexcept
        {
            m_.clear(std::memory_order_release);
        }
    };

#if defined(NDEBUG)
    #define logln(...)  (std::clog << "note: " << std::format(__VA_ARGS__) << '\n')
    #define warnln(...) (std::clog << "warning: " << std::format(__VA_ARGS__) << '\n')
    #define errln(...)  (std::clog << "error: " << std::format(__VA_ARGS__) << '\n')
#else
    #define logln(...)                                                                                              \
        (std::clog << std::format("{}:{}:{}: note: ", __FILE__, __LINE__, std::source_location::current().column()) \
                   << std::format(__VA_ARGS__) << '\n')
    #define warnln(...)                                                                                                \
        (std::cout << std::format("{}:{}:{}: warning: ", __FILE__, __LINE__, std::source_location::current().column()) \
                   << std::format(__VA_ARGS__) << '\n')
    #define errln(...)                                                                                               \
        (std::cerr << std::format("{}:{}:{}: error: ", __FILE__, __LINE__, std::source_location::current().column()) \
                   << std::format(__VA_ARGS__) << '\n')
#endif

    template <typename... F>
    inline constexpr i_::overload_call_t<F...> //
    overload(F&&... funcs) noexcept
    {
        return i_::overload_call_t{std::forward<F>(funcs)...};
    }
}; // namespace STD_EXT_HPP_NAMESPACE

namespace STD_EXT_HPP_NAMESPACE::literals
{
    using namespace std::chrono_literals;
    using namespace std::string_literals;
    using namespace std::string_view_literals;

    inline consteval std::size_t //
    operator""_b(unsigned long long size) noexcept
    {
        return size;
    }

    inline consteval std::size_t //
    operator""_kb(unsigned long long size) noexcept
    {
        return 1024_b * size;
    }

    inline consteval std::size_t //
    operator""_mb(unsigned long long size) noexcept
    {
        return 1024_kb * size;
    }

    inline consteval std::size_t //
    operator""_gb(unsigned long long size) noexcept
    {
        return 1024_mb * size;
    }

    inline consteval std::size_t //
    operator""_kb(long double sizef) noexcept
    {
        return 1024_b * sizef;
    }

    inline consteval std::size_t //
    operator""_mb(long double sizef) noexcept
    {
        return 1024_kb * sizef;
    }

    inline consteval std::size_t //
    operator""_gb(long double sizef) noexcept
    {
        return 1024_mb * sizef;
    }

    inline consteval std::int8_t //
    operator""_i8(unsigned long long i) noexcept
    {
        return static_cast<i8>(i);
    }

    inline consteval std::uint8_t //
    operator""_u8(unsigned long long i) noexcept
    {
        return static_cast<u8>(i);
    }

    inline consteval std::int16_t //
    operator""_i16(unsigned long long i) noexcept
    {
        return static_cast<i16>(i);
    }

    inline consteval std::uint16_t //
    operator""_u16(unsigned long long i) noexcept
    {
        return static_cast<u16>(i);
    }

    inline consteval std::int32_t //
    operator""_i32(unsigned long long i) noexcept
    {
        return static_cast<i32>(i);
    }

    inline consteval std::uint32_t //
    operator""_u32(unsigned long long i) noexcept
    {
        return static_cast<u32>(i);
    }

    inline consteval std::int64_t //
    operator""_i64(unsigned long long i) noexcept
    {
        return static_cast<i64>(i);
    }

    inline consteval std::uint64_t //
    operator""_u64(unsigned long long i) noexcept
    {
        return static_cast<u64>(i);
    }

    inline consteval std::intmax_t //
    operator""_imax(unsigned long long i) noexcept
    {
        return static_cast<imax>(i);
    }

    inline consteval std::uintmax_t //
    operator""_umax(unsigned long long i) noexcept
    {
        return static_cast<umax>(i);
    }

    inline consteval std::size_t //
    operator""_usz(unsigned long long i) noexcept
    {
        return static_cast<usz>(i);
    }

    inline consteval std::ptrdiff_t //
    operator""_ssz(unsigned long long i) noexcept
    {
        return static_cast<ssz>(i);
    }

    inline consteval std::ptrdiff_t //
    operator""_ptrdiff(unsigned long long i) noexcept
    {
        return static_cast<ptrdiff>(i);
    }

    inline consteval std::uintptr_t //
    operator""_uptr(unsigned long long i) noexcept
    {
        return static_cast<uptr>(i);
    }

    inline consteval std::intptr_t //
    operator""_iptr(unsigned long long i) noexcept
    {
        return static_cast<iptr>(i);
    }

    inline consteval float //
    operator""_f32(long double f) noexcept
    {
        return static_cast<f32>(f);
    }

    inline consteval float //
    operator""_f64(long double f) noexcept
    {
        return static_cast<f64>(f);
    }

    inline consteval float //
    operator""_flong(long double f) noexcept
    {
        return static_cast<flong>(f);
    }

}; // namespace STD_EXT_HPP_NAMESPACE::literals

#if !defined(STD_EXT_NO_NAMESPACE)
using namespace STD_EXT_HPP_NAMESPACE;
using namespace STD_EXT_HPP_NAMESPACE::literals;

namespace std
{
    namespace fs = std::filesystem;
};

template <std::unsigned_integral Idx, ts_idx_string_literal Name, std::size_t Class>
struct std::hash<ts_idx<Idx, Name, Class>>
{
    inline static constexpr std::size_t //
    operator()(const ts_idx<Idx, Name, Class>& s) noexcept
    {
        return std::hash<Idx>()(s.number());
    }
};

    #define castc const_cast
    #define castd dynamic_cast
    #define castr reinterpret_cast
    #define casts static_cast

    #define malloc2(type)        reinterpret_cast<type*>(std::malloc(sizeof(type)))
    #define calloc2(count, type) reinterpret_cast<type*>(std::calloc(count, sizeof(type)))

    #define panic() std::terminate()
    #define panic_if0_(condition)                                    \
        if (condition)                                               \
        {                                                            \
            std::cerr << std::format("CRASHED: ({})\n", #condition); \
            panic();                                                 \
        }
    #define panic_if1_(condition, reasons)                                        \
        if (condition)                                                            \
        {                                                                         \
            std::cerr << std::format("CRASHED: ({}): {}\n", #condition, reasons); \
            panic();                                                              \
        }

    #define expand_panic_if_(x)              x
    #define get_panic_if_(_0, _1, name, ...) name
    #define panic_if(...) expand_panic_if_(get_panic_if_(__VA_ARGS__, panic_if1_, panic_if0_)(__VA_ARGS__))

#endif

// static assert section
static_assert(STD_EXT_HPP_NAMESPACE::widthof(static_cast<STD_EXT_HPP_NAMESPACE::u8>(0)) == 8);
static_assert(STD_EXT_HPP_NAMESPACE::widthof(static_cast<STD_EXT_HPP_NAMESPACE::u16>(0)) == 16);
static_assert(STD_EXT_HPP_NAMESPACE::widthof(static_cast<STD_EXT_HPP_NAMESPACE::u32>(0)) == 32);
static_assert(STD_EXT_HPP_NAMESPACE::widthof(static_cast<STD_EXT_HPP_NAMESPACE::u64>(0)) == 64);

static_assert(STD_EXT_HPP_NAMESPACE::widthof(static_cast<STD_EXT_HPP_NAMESPACE::char8>(0)) == 8);
static_assert(STD_EXT_HPP_NAMESPACE::widthof(static_cast<STD_EXT_HPP_NAMESPACE::char16>(0)) == 16);
static_assert(STD_EXT_HPP_NAMESPACE::widthof(static_cast<STD_EXT_HPP_NAMESPACE::char32>(0)) == 32);

static_assert(STD_EXT_HPP_NAMESPACE::widthof(static_cast<STD_EXT_HPP_NAMESPACE::f32>(0)) == 32);
static_assert(STD_EXT_HPP_NAMESPACE::widthof(static_cast<STD_EXT_HPP_NAMESPACE::f64>(0)) == 64);

static_assert(STD_EXT_HPP_NAMESPACE::cmp_to_integral(std::strong_ordering::less) //
              == STD_EXT_HPP_NAMESPACE::cmp_result::less);
static_assert(STD_EXT_HPP_NAMESPACE::cmp_to_integral(std::strong_ordering::equivalent) //
              == STD_EXT_HPP_NAMESPACE::cmp_result::equivalent);
static_assert(STD_EXT_HPP_NAMESPACE::cmp_to_integral(std::strong_ordering::greater) //
              == STD_EXT_HPP_NAMESPACE::cmp_result::greater);
static_assert(STD_EXT_HPP_NAMESPACE::cmp_to_integral(std::weak_ordering::less) //
              == STD_EXT_HPP_NAMESPACE::cmp_result::less);
static_assert(STD_EXT_HPP_NAMESPACE::cmp_to_integral(std::weak_ordering::equivalent) //
              == STD_EXT_HPP_NAMESPACE::cmp_result::equivalent);
static_assert(STD_EXT_HPP_NAMESPACE::cmp_to_integral(std::weak_ordering::greater) //
              == STD_EXT_HPP_NAMESPACE::cmp_result::greater);
static_assert(STD_EXT_HPP_NAMESPACE::cmp_to_integral(std::partial_ordering::less) //
              == STD_EXT_HPP_NAMESPACE::cmp_result::less);
static_assert(STD_EXT_HPP_NAMESPACE::cmp_to_integral(std::partial_ordering::equivalent) //
              == STD_EXT_HPP_NAMESPACE::cmp_result::equivalent);
static_assert(STD_EXT_HPP_NAMESPACE::cmp_to_integral(std::partial_ordering::greater) //
              == STD_EXT_HPP_NAMESPACE::cmp_result::greater);

#endif // STD_EXTENTION_HXX
