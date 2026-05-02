#include <forward_list>
#include <ranges>
#include <vector>

#include <gtest/gtest.h>

#include "mse.hpp"

TEST(MSE, EmptyRange) {
    // Act
    const auto res = dts::ranges::mse(std::views::empty<int>);

    // Assert
    ASSERT_FALSE(res.has_value());
}

TEST(MSE, NonEmptyForwardRange) {
    // Assign
    const std::forward_list src{8, 4, 5, 2, 11, 9, 7, 18, 3};
    const std::forward_list ref{7, 5, 5, 3, 13, 6, 7, 20, 0};
    std::ranges::view auto errors =
        std::views::zip(src, ref) | std::views::transform([](auto pair) static {
            return std::get<0>(pair) - std::get<1>(pair);
        });
    static_assert(std::ranges::forward_range<decltype(errors)>);

    // Act
    const auto res = dts::ranges::mse(errors);

    // Assert
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(*res, 29.0 / 9.0);
}

TEST(MSE, NonEmptyRandomAccessRange) {
    // Assign
    const std::vector src{8, 4, 5, 2, 11, 9, 7, 18, 3};
    const std::vector ref{7, 5, 5, 3, 13, 6, 7, 20, 0};
    std::ranges::view auto errors =
        std::views::zip(src, ref) | std::views::transform([](auto pair) static {
            return std::get<0>(pair) - std::get<1>(pair);
        });
    static_assert(std::ranges::random_access_range<decltype(errors)>);

    // Act
    const auto res = dts::ranges::mse(errors);

    // Assert
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(*res, 29.0 / 9.0);
}
