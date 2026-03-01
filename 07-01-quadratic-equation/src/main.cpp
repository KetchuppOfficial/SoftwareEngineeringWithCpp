#include <cassert>
#include <cmath>
#include <concepts>
#include <format>
#include <iostream>
#include <optional>
#include <print>
#include <stdexcept>
#include <variant>

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
std::optional<std::pair<double, double>> solve_quadratic(double a, double b, double c) {
    assert(!cmp::is_zero(a));

    const auto D = to_zero(b * b - 4 * a * c);
    if (D < 0) {
        return {};
    }

    const auto square_root_of_d = std::sqrt(D);
    const auto twice_a = 2 * a;
    const auto x1 = (-b - square_root_of_d) / twice_a;
    const auto x2 = (-b + square_root_of_d) / twice_a;
    return {{x1, x2}};
}

using InfRoots = std::monostate;
using OneRoot = double;
using TwoRoots = std::pair<OneRoot, OneRoot>;

std::optional<std::variant<InfRoots, OneRoot, TwoRoots>> solve(double a, double b, double c) {
    if (!cmp::is_zero(a)) {
        return solve_quadratic(a, b, c).and_then([](const auto &pair) static {
            using RetType = decltype(solve(0, 0, 0));
            return RetType{pair};
        });
    }

    if (!cmp::is_zero(b)) {
        return solve_linear(b, c);
    }

    if (cmp::is_zero(c)) {
        return std::monostate{};
    }

    return {};
}

} // unnamed namespace

int main() try {
    const auto a = get_coefficient('a');
    const auto b = get_coefficient('b');
    const auto c = get_coefficient('c');

    if (const auto maybe_roots = solve(a, b, c); !maybe_roots.has_value()) {
        std::println("no roots");
    } else if (const auto &roots = *maybe_roots; std::holds_alternative<InfRoots>(roots)) {
        std::println("infinite number of roots");
    } else if (const auto *one_root = std::get_if<OneRoot>(&roots)) {
        std::println("one root: {}", *one_root);
    } else if (const auto *two_roots = std::get_if<TwoRoots>(&roots)) {
        std::println("two roots: ({:.2f}, {:.2f})", two_roots->first, two_roots->second);
    }
} catch (const std::exception &e) {
    std::println(stderr, "Caught an instance of {}.\nwhat(): {}", typeid(e).name(), e.what());
    return EXIT_FAILURE;
} catch (...) {
    std::println(stderr, "Caught an unknown exception.");
    return EXIT_FAILURE;
}
