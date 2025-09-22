#include <cassert>
#include <cmath>
#include <complex>
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
    double x{};
    std::cin >> x;
    if (const auto state = std::cin.rdstate(); state == std::ios_base::goodbit) {
        return x;
    } else if (state & std::ios_base::badbit) {
        throw std::runtime_error{
            std::format("error occurred while reading coefficient \'{}\'", coeff)};
    } else if (state & std::ios_base::eofbit) {
        if (!(state & std::ios_base::failbit)) {
            return x;
        }
    }
    throw std::runtime_error{std::format("error occurred while reading coefficient \'{}\'", coeff)};
}

// Equation: b * x + c = 0, b != 0
double solve_linear(double b, double c) {
    assert(!cmp::is_zero(b));
    return -c / b;
}

double to_zero(double x) {
    if (cmp::is_zero(x)) {
        return 0.0;
    }
    return x;
}

// Equation: a * x^2 + b * x + c = 0, a != 0
std::pair<std::complex<double>, std::complex<double>> solve_quadratic(double a, double b,
                                                                      double c) {
    assert(!cmp::is_zero(a));

    const auto square_root_of_d = std::sqrt(std::complex{to_zero(b * b - 4 * a * c)});
    const auto twice_a = 2 * a;
    const auto x1 = (-b - square_root_of_d) / twice_a;
    const auto x2 = (-b + square_root_of_d) / twice_a;
    return {x1, x2};
}

char sign(double x) { return x < 0 ? '-' : '+'; }

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
            std::println(std::cout, "one root: {}", solve_linear(b, c));
        }
    } else {
        const auto [x1, x2] = solve_quadratic(a, b, c);

        if (cmp::is_zero(x1.imag())) {
            if (cmp::is_zero(x2.imag())) {
                std::println(std::cout, "two roots: ({:.2f}, {:.2f})", x1.real(), x2.real());
            } else {
                std::println(std::cout, "two roots: ({:.2f}, {:.2f} {} {:.2f}i)", x1.real(),
                             x2.real(), sign(x2.imag()), std::abs(x2.imag()));
            }
        } else if (cmp::is_zero(x2.imag())) {
            std::println(std::cout, "two roots: ({:.2f} {} {:.2f}i, {:.2f})", x1.real(),
                         sign(x1.imag()), std::abs(x1.imag()), x2.real());
        } else {
            std::println(std::cout, "two roots: ({:.2f} {} {:.2f}i, {:.2f} {} {:.2f}i)", x1.real(),
                         sign(x1.imag()), std::abs(x1.imag()), x2.real(), sign(x2.imag()),
                         std::abs(x2.imag()));
        }
    }

    return 0;
} catch (const std::exception &e) {
    std::println(stderr, "Caught an instance of {}.\nwhat(): {}", typeid(e).name(), e.what());
    return EXIT_FAILURE;
} catch (...) {
    std::println(stderr, "Caught an unknown exception.");
    return EXIT_FAILURE;
}
