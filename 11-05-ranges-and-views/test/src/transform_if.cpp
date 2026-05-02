#include <iterator>
#include <ranges>
#include <vector>

#include <gtest/gtest.h>

#include "transform_if.hpp"

TEST(TransformIf, Iterators) {
    // Assign
    const std::vector<std::pair<int, int>> src{
        std::from_range, std::views::zip(std::views::iota(0, 10), std::views::repeat(0))};
    std::vector<int> dst;

    // Act
    dts::ranges::transform_if(
        src.begin(), src.end(), std::back_inserter(dst), [](int n) { return n * n; },
        [](int n) { return n % 2 == 0; }, &std::pair<int, int>::first);

    // Assert
    EXPECT_EQ(dst, (std::vector{0, 4, 16, 36, 64}));
}

TEST(TransformIf, Range) {
    // Assign
    const std::vector<std::pair<int, int>> src{
        std::from_range, std::views::zip(std::views::iota(0, 10), std::views::repeat(0))};
    std::vector<int> dst;

    // Act
    dts::ranges::transform_if(
        src, std::back_inserter(dst), [](int n) { return n * n; }, [](int n) { return n % 2 == 0; },
        &std::pair<int, int>::first);

    // Assert
    EXPECT_EQ(dst, (std::vector{0, 4, 16, 36, 64}));
}
