#ifndef INCLUDE_STATISTICS_HPP
#define INCLUDE_STATISTICS_HPP

#include <algorithm>
#include <concepts>

namespace dts {

template <typename... Args>
concept PackOfDoubles = (std::same_as<Args, double> && ...);

template <typename... Args>
    requires PackOfDoubles<Args...>
constexpr double variadic_max(double arg, Args... args) {
    if constexpr (sizeof...(Args) == 0) {
        return arg;
    } else {
        return std::max(arg, variadic_max(args...));
    }
}

template <typename... Args>
    requires PackOfDoubles<Args...>
constexpr double variadic_min(double arg, Args... args) {
    if constexpr (sizeof...(Args) == 0) {
        return arg;
    } else {
        return std::min(arg, variadic_min(args...));
    }
}

template <typename... Args>
concept NonEmptyPackOfDoubles = (sizeof...(Args) > 0) && PackOfDoubles<Args...>;

template <typename... Args>
    requires NonEmptyPackOfDoubles<Args...>
constexpr double variadic_sum(Args... args) {
    return (args + ...);
}

template <typename... Args>
    requires NonEmptyPackOfDoubles<Args...>
constexpr double variadic_mean(Args... args) {
    return variadic_sum(args...) / sizeof...(Args);
}

} // namespace dts

#endif // INCLUDE_STATISTICS_HPP
