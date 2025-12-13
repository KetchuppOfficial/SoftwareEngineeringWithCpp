#ifndef INCLUDE_PI_HPP
#define INCLUDE_PI_HPP

#include <cmath>
#include <concepts>
#include <ranges>

namespace dts {

template <std::floating_point T>
consteval T compute_pi(T epsilon) {
    T quoter_pi = 1;
    T numerator = -1;
    for (const auto k : std::views::iota(1uz)) {
        const auto elem = numerator / (2 * k + 1);
        if (std::abs(elem) < epsilon) {
            break;
        }
        quoter_pi += elem;
        numerator = -numerator;
    }
    return quoter_pi * 4;
}

} // namespace dts

#endif // INCLUDE_PI_HPP
