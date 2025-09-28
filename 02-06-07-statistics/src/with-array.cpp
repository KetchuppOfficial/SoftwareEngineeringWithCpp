#include <array>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <ranges>
#include <stdexcept>

#include "statistics.hpp"

int main() try {
    constexpr std::size_t kMaxElements = 1000;
    std::array<double, kMaxElements> numbers{};
    const auto n_elems = [&numbers] -> std::size_t {
        for (const auto i : std::views::iota(0uz, numbers.size())) {
            double elem{};
            std::cin >> elem;
            if (const auto state = std::cin.rdstate(); state == std::ios_base::goodbit) {
                numbers[i] = elem;
            } else if (state & std::ios_base::badbit) {
                throw std::runtime_error{"badbit set"};
            } else if (state & std::ios_base::eofbit) {
                if (state & std::ios_base::failbit) {
                    return i;
                } else {
                    numbers[i] = elem;
                    return i + 1;
                }
            } else {
                throw std::runtime_error{"failbit without eofbit set"};
            }
        }
        throw std::runtime_error{"too many elements requested"};
    }();

    auto begin = numbers.begin();
    auto end = std::next(begin, n_elems);

    auto min_elem_it = dts::min_element(begin, end);
    auto max_elem_it = dts::max_element(begin, end);
    auto maybe_mean = dts::mean(begin, end);
    if (!maybe_mean.has_value()) {
        throw std::runtime_error{"the range is empty"};
    }
    auto maybe_std_deviation = dts::standard_deviation(begin, end);
    if (!maybe_std_deviation.has_value()) {
        throw std::runtime_error{"the range is empty"};
    }

    std::println(std::cout, "min:                {}", *min_elem_it);
    std::println(std::cout, "max:                {}", *max_elem_it);
    std::println(std::cout, "mean:               {}", *maybe_mean);
    std::println(std::cout, "standard deviation: {}", *maybe_std_deviation);

    return 0;
} catch (const std::exception &e) {
    std::println(std::cerr, "Caught an instance of {}.\nwhat(): {}", typeid(e).name(), e.what());
    return EXIT_FAILURE;
} catch (...) {
    std::println(std::cerr, "Caught an unknown exception.");
    return EXIT_FAILURE;
}
