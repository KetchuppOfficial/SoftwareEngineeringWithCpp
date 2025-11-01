#include <deque>
#include <format>

#include <gtest/gtest.h>

#include "quick_sort.hpp"

TEST(QuickSort, EmptySequence) {
    // Assign
    std::deque<int> d;

    // Act
    dts::sort(d.begin(), d.end());

    // Assert
    EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, OneElement) {
    // Assign
    std::deque<int> d{42};

    // Act
    dts::sort(d.begin(), d.end());

    // Assert
    EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, TwoElementsSorted) {
    // Assign
    std::deque<int> d{1, 2};

    // Act
    dts::sort(d.begin(), d.end());

    // Assert
    EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, TwoElementsNotSorted) {
    // Assign
    std::deque<int> d{2, 1};

    // Act
    dts::sort(d.begin(), d.end());

    // Assert
    EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, TwoElementsEqual) {
    // Assign
    std::deque<int> d{1, 1};

    // Act
    dts::sort(d.begin(), d.end());

    // Assert
    EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, RelativelyLongUnsortedSequence) {
    // Assign
    std::deque<int> d{-5, 1, 12, 2, 8, 9, 5, 8, 11, -12, 37, 42, 1, 35};

    // Act
    dts::sort(d.begin(), d.end());

    // Assert
    EXPECT_TRUE(std::ranges::is_sorted(d)) << std::format("{}", d);
}

TEST(QuickSort, RelativelyLongUnsortedSequenceWithOtherComparator) {
    // Assign
    std::deque<int> d{-5, 1, 12, 2, 8, 9, 5, 8, 11, -12, 37, 42, 1, 35};
    std::greater cmp;

    // Act
    dts::sort(d.begin(), d.end(), cmp);

    // Assert
    EXPECT_TRUE(std::ranges::is_sorted(d, cmp)) << std::format("{}", d);
}
