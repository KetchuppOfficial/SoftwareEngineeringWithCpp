#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "statistics.hpp"

int main() try {
    std::vector<double> numbers;
    for (;;) {
        double elem{};
        std::cin >> elem;
        if (const auto state = std::cin.rdstate(); state == std::ios_base::goodbit) {
            numbers.push_back(elem);
        } else if (state & std::ios_base::badbit) {
            throw std::runtime_error{"badbit set"};
        } else if (state & std::ios_base::eofbit) {
            if (!(state & std::ios_base::failbit)) {
                numbers.push_back(elem);
            }
            break;
        } else {
            throw std::runtime_error{"failbit without eofbit set"};
        }
    }

    auto min_elem_it = dts::min_element(numbers.begin(), numbers.end());
    auto max_elem_it = dts::max_element(numbers.begin(), numbers.end());
    auto maybe_mean = dts::mean(numbers.begin(), numbers.end());
    if (!maybe_mean.has_value()) {
        throw std::runtime_error{"the range is empty"};
    }
    auto maybe_std_deviation = dts::standard_deviation(numbers.begin(), numbers.end());
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
