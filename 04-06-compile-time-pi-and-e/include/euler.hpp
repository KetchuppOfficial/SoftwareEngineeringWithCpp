#ifndef INCLUDE_EULER_HPP
#define INCLUDE_EULER_HPP

#include <cmath>
#include <concepts>
#include <ranges>

namespace dts {

template <std::floating_point T>
consteval T compute_e(T epsilon) {
    T e = 1;
    T elem = 1;
    for (const auto k : std::views::iota(0uz)) {
        elem /= (k + 1);
        if (std::abs(elem) < epsilon) {
            break;
        }
        e += elem;
    }
    return e;
}

} // namespace dts

#endif // INCLUDE_EULER_HPP
