#ifndef INCLUDE_STATISTICS_HPP
#define INCLUDE_STATISTICS_HPP

#include <cmath>
#include <iterator>
#include <numeric>
#include <optional>
#include <utility>

// just std backwards
namespace dts {

template <std::forward_iterator It>
It min_element(It first, It last) {
    if (first == last) {
        return last;
    }

    auto smallest = first;
    while (++first != last) {
        if (*first < *smallest) {
            smallest = first;
        }
    }

    return smallest;
}

template <std::forward_iterator It>
It max_element(It first, It last) {
    if (first == last) {
        return last;
    }

    auto largest = first;
    while (++first != last) {
        if (*largest < *first) {
            largest = first;
        }
    }

    return largest;
}

template <std::forward_iterator It>
std::optional<std::iter_value_t<It>> mean(It first, It last) {
    if (first == last) {
        return std::nullopt;
    }

    if constexpr (std::random_access_iterator<It>) {
        return std::accumulate(first, last, std::iter_value_t<It>{}) / (last - first);
    } else {
        std::iter_value_t<It> sum{};
        std::iter_difference_t<It> distance = 0;
        for (; first != last; ++first) {
            sum = std::move(sum) + *first;
            ++distance;
        }
        return std::move(sum) / distance;
    }
}

template <typename T>
concept SupportsSquareRoot = requires(T v) { std::sqrt(v); };

template <std::forward_iterator It>
    requires SupportsSquareRoot<std::iter_value_t<It>>
std::optional<std::iter_value_t<It>> standard_deviation(It first, It last) {
    if (first == last) {
        return std::nullopt;
    }

    const auto [mean, distance] = [first, last] {
        if constexpr (std::random_access_iterator<It>) {
            const auto distance = last - first;
            return std::pair{std::accumulate(first, last, std::iter_value_t<It>{}) / distance,
                             distance};
        } else {
            std::iter_value_t<It> sum{};
            std::iter_difference_t<It> distance = 0;
            for (; first != last; ++first) {
                sum = std::move(sum) + *first;
                ++distance;
            }
            return std::pair{sum / distance, distance};
        }
    }();

    const auto dispersion =
        std::accumulate(first, last, std::iter_value_t<It>{},
                        [mean](auto &&init, const auto &val) {
                            const auto deviation = val - mean;
                            return std::forward<decltype(init)>(init) + deviation * deviation;
                        }) /
        distance;

    return std::sqrt(dispersion);
}

} // namespace dts

#endif // INCLUDE_STATISTICS_HPP
