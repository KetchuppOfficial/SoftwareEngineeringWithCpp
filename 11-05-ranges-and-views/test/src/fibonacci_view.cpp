#include <array>
#include <ranges>

#include <gtest/gtest.h>

#include "fibonacci_view.hpp"

TEST(FibonacciView, Simple) {
    // Act
    std::ranges::view auto fib_view = dts::views::fibonacci | std::views::take(10);

    // Assert
    EXPECT_TRUE(std::ranges::equal(fib_view, std::array{0, 1, 1, 2, 3, 5, 8, 13, 21, 34}));
}
