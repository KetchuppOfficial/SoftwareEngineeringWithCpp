#ifndef INCLUDE_MAE_HPP
#define INCLUDE_MAE_HPP

#include <algorithm>
#include <cmath>
#include <iterator>
#include <optional>
#include <ranges>
#include <utility>

namespace dts {

template <typename T>
concept SupportsAbs = requires(const T &value) { std::abs(value); };

namespace ranges {

template <std::ranges::input_range R>
    requires SupportsAbs<std::ranges::range_value_t<R>> &&
             std::convertible_to<std::ranges::range_value_t<R>, double>
std::optional<double> mae(R &&errors) {
    if (std::ranges::empty(errors)) {
        return std::nullopt;
    }

    using value_t = std::ranges::range_value_t<R>;

    if constexpr (std::ranges::random_access_range<R>) {
        const auto n_elems = std::ranges::distance(errors);
        const auto sum =
            std::ranges::fold_left(std::forward<R>(errors), value_t{}, [](auto &&sum, auto &&elem) {
                return std::forward<decltype(sum)>(sum) +
                       std::abs(std::forward<decltype(elem)>(elem));
            });
        return static_cast<double>(sum) / n_elems;
    } else {
        value_t sum{};
        std::ranges::range_difference_t<R> distance = 0;
        for (auto &&elem : std::forward<R>(errors)) {
            sum = std::move(sum) + std::abs(std::forward<decltype(elem)>(elem));
            ++distance;
        }
        return static_cast<double>(sum) / distance;
    }
}

} // namespace ranges

} // namespace dts

#endif // INCLUDE_MAE_HPP
