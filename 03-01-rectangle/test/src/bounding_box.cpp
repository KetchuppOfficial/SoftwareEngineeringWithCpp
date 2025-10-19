#include <vector>

#include <gtest/gtest.h>

#include "rectangle.hpp"

TEST(BoundingBox, AllRectanglesAreNestedInsideEachOther) {
    // Assign
    const std::vector<dts::Rectangle> rectangles{{dts::Point{0, 0}, 5, 5},
                                                 {dts::Point{0, 0}, 4, 4},
                                                 {dts::Point{0, 0}, 3, 3},
                                                 {dts::Point{0, 0}, 2, 2},
                                                 {dts::Point{0, 0}, 1, 1}};

    // Act
    const auto bb = dts::bounding_box(rectangles.begin(), rectangles.end());

    // Assert
    EXPECT_EQ(bb, rectangles.front());
}

TEST(BoundingBox, RectanglesDoNotIntersect) {
    // Assign
    const std::vector<dts::Rectangle> rectangles{{dts::Point{0, 0}, 1, 1},
                                                 {dts::Point{1, 1}, 1, 1},
                                                 {dts::Point{2, 2}, 1, 1},
                                                 {dts::Point{2, 0}, 1, 1},
                                                 {dts::Point{0, 2}, 1, 1}};
    const dts::Rectangle expected{dts::Point{0, 0}, 3, 3};

    // Act
    const auto bb = dts::bounding_box(rectangles.begin(), rectangles.end());

    // Assert
    EXPECT_EQ(bb, expected);
}
