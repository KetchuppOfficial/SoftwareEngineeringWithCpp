#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <optional>
#include <print>
#include <ranges>
#include <string_view>
#include <utility>
#include <vector>

namespace {

using Ratio = std::optional<std::pair<std::size_t, std::size_t>>;

template <std::ranges::input_range R>
Ratio growth_ratio(R &&capacities) {
    std::ranges::view auto windows = std::forward<R>(capacities) | std::views::adjacent<2>;
    const auto [first, second] = windows.front();
    if (std::ranges::all_of(windows, [first, second](auto tup) {
            return std::get<1>(tup) * first == std::get<0>(tup) * second;
        })) {

        if (second % first) {
            return {{second, first}};
        } else {
            return {{second / first, 1}};
        }
    }

    return std::nullopt;
}

Ratio vector_reallocation_coeff(std::size_t reallocations) {
    std::vector<int> v{0};
    std::vector<std::size_t> capacities{v.capacity()};

    for (;;) {
        v.push_back(0);
        if (const auto capacity = v.capacity(); capacity != capacities.back()) {
            capacities.push_back(capacity);
            --reallocations;
            if (reallocations == 0) {
                break;
            }
        }
    }

    return growth_ratio(capacities);
}

Ratio deque_reallocation_coeff(std::size_t reallocations) {
    std::deque<int> d{0};
    std::vector<const int *> addresses{&d.back(), &d.back() + 1};

    for (;;) {
        d.push_back(0);
        if (const int *addr = &d.back(); addr == addresses.back()) {
            addresses.back() += 1;
        } else {
            addresses.append_range(std::array{addr, addr + 1});
            --reallocations;
            if (reallocations == 0) {
                break;
            }
        }
    }

    return growth_ratio(addresses | std::views::chunk(2) | std::views::transform([](auto tup) {
                            auto [front_addr, back_addr] = tup;
                            return (back_addr - front_addr) * sizeof(int);
                        }) |
                        std::ranges::to<std::vector<std::size_t>>());
}

using MeasurementFunc = Ratio (*)(std::size_t);

void print_result(MeasurementFunc f, std::string_view prefix) {
    constexpr std::size_t kReallocations = 5;

    if (const auto maybe_ratio = f(kReallocations)) {
        std::println("{} increases in size as: {}/{}", prefix, maybe_ratio->first,
                     maybe_ratio->second);
    } else {
        std::println("{} increases in size non-exponentially", prefix);
    }
}

} // unnamed namespace

int main() try {
    using namespace std::string_view_literals;
    print_result(vector_reallocation_coeff, "buffer of std::vector"sv);
    print_result(deque_reallocation_coeff, "blocks of std::deque"sv);
} catch (const std::exception &e) {
    std::println(stderr, "Caught an instance of {}\nwhat(): {}", typeid(e).name(), e.what());
    return EXIT_FAILURE;
} catch (...) {
    std::println(stderr, "Caught an unknown exception");
    return EXIT_FAILURE;
}
