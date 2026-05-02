#ifndef INCLUDE_MSE_HPP
#define INCLUDE_MSE_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <optional>
#include <ranges>
#include <utility>

namespace dts::ranges {

template <std::ranges::input_range R>
    requires std::convertible_to<std::ranges::range_value_t<R>, double>
std::optional<double> mse(R &&errors) {
    if (std::ranges::empty(errors)) {
        return std::nullopt;
    }

    using value_t = std::ranges::range_value_t<R>;

    if constexpr (std::ranges::random_access_range<R>) {
        const auto n_elems = std::ranges::distance(errors);
        const auto sum = std::ranges::fold_left(
            std::forward<R>(errors) |
                std::views::transform([](const auto &v) static { return v * v; }),
            value_t{}, std::plus<>{});
        return static_cast<double>(sum) / n_elems;
    } else {
        value_t sum{};
        std::ranges::range_difference_t<R> distance = 0;
        for (const auto &elem : std::forward<R>(errors)) {
            sum = std::move(sum) + elem * elem;
            ++distance;
        }
        return static_cast<double>(sum) / distance;
    }
}

} // namespace dts::ranges

#endif // INCLUDE_MSE_HPP
