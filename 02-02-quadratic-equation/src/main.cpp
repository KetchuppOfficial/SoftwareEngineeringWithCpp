#include <cassert>
#include <cmath>
#include <concepts>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <format>
#include <iostream>
#include <print>
#include <stdexcept>
#include <utility>

namespace cmp {

template <std::floating_point T>
static constexpr T epsilon = 1e-6;

template <std::floating_point T>
static constexpr bool is_zero(T value, T zero_diff = epsilon<T>) {
    return std::abs(value) < zero_diff;
}

} // namespace cmp

namespace {

double get_coefficient(char coeff) {
    double x;
    std::cin >> x;
    if (!std::cin.good()) {
        throw std::runtime_error{
            std::format("error occurred while reading coefficient \'{}\'", coeff)};
    }
    return x;
}

// Equation: b * x + c = 0, b != 0
double solve_linear(double b, double c) {
    assert(!cmp::is_zero(b));
    return -c / b;
}

// Equation: a * x^2 + b * x + c = 0, a != 0
std::pair<double, double> solve_quadratic(double a, double b, double c) {
    assert(!cmp::is_zero(a));
    const auto square_root_of_d = std::sqrt(b * b + 4 * a * c);
    const auto twice_a = 2 * a;
    return {(-b - square_root_of_d) / twice_a, (-b + square_root_of_d) / twice_a};
}

} // unnamed namespace

int main() try {
    const auto a = get_coefficient('a');
    const auto b = get_coefficient('b');
    const auto c = get_coefficient('c');

    if (cmp::is_zero(a)) {
        if (cmp::is_zero(b)) {
            if (cmp::is_zero(c)) {
                std::cout << "any number\n";
            } else {
                std::cout << "no roots\n";
            }
        } else {
            std::cout << "one root: " << solve_linear(b, c) << '\n';
        }
    } else {
        const auto [x1, x2] = solve_quadratic(a, b, c);
        std::cout << "two roots: (" << x1 << ", " << x2 << ")\n";
    }

    return 0;
} catch (const std::exception &e) {
    std::println(stderr, "Caught an instance of {}.\nwhat(): {}", typeid(e).name(), e.what());
    return EXIT_FAILURE;
} catch (...) {
    std::println(stderr, "Caught an unknown exception.");
    return EXIT_FAILURE;
}
