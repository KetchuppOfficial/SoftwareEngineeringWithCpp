#include <array>
#include <iterator>
#include <ranges>

#include <gtest/gtest.h>

#include "fibonacci_iterator.hpp"

TEST(FibonacciIterator, DefaultConstructed) {
    // Assign
    const dts::FibonacciIterator it;

    // Act & Assert
    EXPECT_EQ(*it, 0);
}

TEST(FibonacciIterator, SomeFirstNumbers) {
    // Assign
    const dts::FibonacciIterator it;
    constexpr std::array kFib{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55};

    // Act & Assert
    for (const auto [i, n] : std::views::enumerate(kFib)) {
        EXPECT_EQ(*std::next(it, i), n);
    }
}
