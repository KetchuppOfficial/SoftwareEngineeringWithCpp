#ifndef INCLUDE_DURATION_HPP
#define INCLUDE_DURATION_HPP

#include "compile_time_ratio.hpp"

namespace dts {

template <typename T, typename R = Ratio<1>>
struct Duration {
    T x{};
};

template <typename T1, typename R1, typename T2, typename R2>
constexpr auto operator+(const Duration<T1, R1> &lhs, const Duration<T2, R2> &rhs) {
    using ratio_t = Ratio<1, sum<R1, R2>::den>;

    auto x =
        (lhs.x * ratio_t::den / R1::den * R1::num) + (rhs.x * ratio_t::den / R2::den * R2::num);

    return Duration<decltype(x), ratio_t>(x);
}

template <typename T1, typename R1, typename T2, typename R2>
constexpr auto operator-(const Duration<T1, R1> &lhs, const Duration<T2, R2> &rhs) {
    return lhs + Duration<T2, R2>{-rhs.x};
}

} // namespace dts

#endif // INCLUDE_DURATION_HPP
