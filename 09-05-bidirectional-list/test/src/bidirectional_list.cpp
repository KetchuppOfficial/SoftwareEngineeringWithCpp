#include <algorithm>
#include <format>
#include <ranges>

#include <gtest/gtest.h>

#include "bidirectional_list.hpp"

std::string to_string(const dts::List<int> &list) {
    using namespace std::string_view_literals;
    auto strings = list | std::views::transform([](int n) static { return std::format("{}", n); });
    return std::format("{}", std::views::join_with(strings, ", "sv));
}

TEST(BidirectionalList, PushBackInEmptyList) {
    // Assign
    dts::List<int> list;

    // Act
    list.push_back(42);

    // Assert
    EXPECT_TRUE(std::ranges::equal(list, std::views::single(42))) << to_string(list);
}

TEST(BidirectionalList, ForwardTraversal) {
    // Assign
    const auto view = std::views::iota(0, 10);
    dts::List<int> list;

    // Act
    for (int n : view) {
        list.push_back(n);
    }

    // Assert
    EXPECT_TRUE(std::ranges::equal(list.begin(), list.end(), view.begin(), view.end()))
        << to_string(list);
}

TEST(BidirectionalList, BackwardTraversal) {
    // Assign
    const auto view = std::views::iota(0, 10);
    const auto rview = view | std::views::reverse;
    dts::List<int> list;

    // Act
    for (const int n : view) {
        list.push_back(n);
    }

    // Assert
    EXPECT_TRUE(std::ranges::equal(list.rbegin(), list.rend(), rview.begin(), rview.end()))
        << to_string(list);
}
