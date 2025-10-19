#include <vector>

#include <gtest/gtest.h>

#include "rectangle.hpp"

TEST(Intersection, FirstAndSecondIntersectByAHorizontalEdge) {
    // Assign
    constexpr unsigned height = 5;
    const dts::Rectangle first{dts::Point{0, 0}, 1, height};
    const dts::Rectangle second{dts::Point{0, height}, 1, 1};

    // Act
    const auto maybe_intersection_1 = dts::Rectangle::intersection(first, second);
    const auto maybe_intersection_2 = dts::Rectangle::intersection(second, first);

    // Assert
    EXPECT_FALSE(maybe_intersection_1);
    EXPECT_FALSE(maybe_intersection_2);
}

TEST(Intersection, FirstIsAboveSecond) {
    // Assign
    constexpr unsigned height = 5;
    const dts::Rectangle first{dts::Point{0, 0}, 1, height};
    const dts::Rectangle second{dts::Point{0, height + 1}, 1, 1};

    // Act
    const auto maybe_intersection_1 = dts::Rectangle::intersection(first, second);
    const auto maybe_intersection_2 = dts::Rectangle::intersection(second, first);

    // Assert
    EXPECT_FALSE(maybe_intersection_1);
    EXPECT_FALSE(maybe_intersection_2);
}

TEST(Intersection, FirstAndSecondIntersectByAVerticalEdge) {
    // Assign
    constexpr unsigned width = 10;
    const dts::Rectangle first{dts::Point{0, 0}, width, 1};
    const dts::Rectangle second{dts::Point{width, 0}, 1, 1};

    // Act
    const auto maybe_intersection_1 = dts::Rectangle::intersection(first, second);
    const auto maybe_intersection_2 = dts::Rectangle::intersection(second, first);

    // Assert
    EXPECT_FALSE(maybe_intersection_1);
    EXPECT_FALSE(maybe_intersection_2);
}

TEST(Intersection, FirstIsOnTheLeftToSecond) {
    // Assign
    constexpr unsigned width = 10;
    const dts::Rectangle first{dts::Point{0, 0}, width, 1};
    const dts::Rectangle second{dts::Point{width + 1, 0}, 1, 1};

    // Act
    const auto maybe_intersection_1 = dts::Rectangle::intersection(first, second);
    const auto maybe_intersection_2 = dts::Rectangle::intersection(second, first);

    // Assert
    EXPECT_FALSE(maybe_intersection_1);
    EXPECT_FALSE(maybe_intersection_2);
}

TEST(Intersection, FirstAndSecondIntersectByTopLeftVertex) {
    // Assign
    constexpr unsigned height = 10;
    constexpr unsigned width = 10;
    const dts::Rectangle first{dts::Point{0, 0}, width, height};
    const dts::Rectangle second{dts::Point{width, height}, width, height};

    // Act
    const auto maybe_intersection_1 = dts::Rectangle::intersection(first, second);
    const auto maybe_intersection_2 = dts::Rectangle::intersection(second, first);

    // Assert
    EXPECT_FALSE(maybe_intersection_1);
    EXPECT_FALSE(maybe_intersection_2);
}

TEST(Intersection, FirstAndSecondIntersectByTopRightVertex) {
    // Assign
    constexpr unsigned height = 10;
    constexpr unsigned width = 10;
    const dts::Rectangle first{dts::Point{0, 0}, width, height};
    const dts::Rectangle second{dts::Point{width, -int{height}}, width, height};

    // Act
    const auto maybe_intersection_1 = dts::Rectangle::intersection(first, second);
    const auto maybe_intersection_2 = dts::Rectangle::intersection(second, first);

    // Assert
    EXPECT_FALSE(maybe_intersection_1);
    EXPECT_FALSE(maybe_intersection_2);
}

TEST(Intersection, OneRectangleBelongsToTheOther) {
    // Assign
    constexpr unsigned height = 10;
    constexpr unsigned width = 10;
    const dts::Rectangle first{dts::Point{0, 0}, width, height};
    const dts::Rectangle second{dts::Point{-int{width}, -int{height}}, 3 * width, 3 * height};

    // Act
    const auto maybe_intersection_1 = dts::Rectangle::intersection(first, second);
    const auto maybe_intersection_2 = dts::Rectangle::intersection(second, first);

    // Assert
    EXPECT_EQ(maybe_intersection_1, first);
    EXPECT_EQ(maybe_intersection_2, first);
}

TEST(Intersection, OneRectangleOverlapsTheOther) {
    // Assign
    constexpr unsigned height = 10;
    constexpr unsigned width = 10;
    const dts::Rectangle first{dts::Point{0, 0}, width, height};
    const dts::Rectangle second{dts::Point{width / 2, height / 2}, width, height};
    const dts::Rectangle expected{dts::Point{width / 2, height / 2}, width / 2, height / 2};

    // Act
    const auto maybe_intersection_1 = dts::Rectangle::intersection(first, second);
    const auto maybe_intersection_2 = dts::Rectangle::intersection(second, first);

    // Assert
    EXPECT_EQ(maybe_intersection_1, expected);
    EXPECT_EQ(maybe_intersection_2, expected);
}

TEST(Intersection, IntersectionsWidthIsTheSameAsOfBothRectangles) {
    // Assign
    constexpr unsigned width = 3;
    constexpr unsigned height = 5;
    constexpr int shift = 2;
    const dts::Rectangle first{dts::Point{0, 0}, width, height};
    const dts::Rectangle second{dts::Point{0, shift}, width, height};
    const dts::Rectangle expected{dts::Point{0, shift}, width, height - shift};

    // Act
    const auto maybe_intersection_1 = dts::Rectangle::intersection(first, second);
    const auto maybe_intersection_2 = dts::Rectangle::intersection(second, first);

    // Assert
    EXPECT_EQ(maybe_intersection_1, expected);
    EXPECT_EQ(maybe_intersection_2, expected);
}

TEST(Intersection, IntersectionsHeightIsTheSameAsOfBothRectangles) {
    // Assign
    constexpr unsigned width = 5;
    constexpr unsigned height = 3;
    constexpr int shift = 2;
    const dts::Rectangle first{dts::Point{0, 0}, width, height};
    const dts::Rectangle second{dts::Point{shift, 0}, width, height};
    const dts::Rectangle expected{dts::Point{shift, 0}, width - shift, height};

    // Act
    const auto maybe_intersection_1 = dts::Rectangle::intersection(first, second);
    const auto maybe_intersection_2 = dts::Rectangle::intersection(second, first);

    // Assert
    EXPECT_EQ(maybe_intersection_1, expected);
    EXPECT_EQ(maybe_intersection_2, expected);
}

TEST(Intersection, ManyRectangles) {
    // Assign
    const std::vector<dts::Rectangle> rectangles{{dts::Point{0, 0}, 3, 3},
                                                 {dts::Point{2, 0}, 3, 3},
                                                 {dts::Point{0, 2}, 3, 3},
                                                 {dts::Point{2, 2}, 3, 3}};
    const dts::Rectangle expected_intersection{dts::Point{2, 2}, 1, 1};

    // Act
    const auto intersection = dts::intersection(rectangles.begin(), rectangles.end());

    // Assert
    EXPECT_EQ(intersection, expected_intersection);
}
