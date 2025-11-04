#include <limits>

#include <gtest/gtest.h>

#include "triangle.hpp"

TEST(Triangle, ConstructorThrowsOnInvalidSide) {
    EXPECT_THROW((dts::Triangle{1.0, 1.0, std::numeric_limits<double>::infinity()}),
                 std::invalid_argument);
    EXPECT_THROW((dts::Triangle{1.0, std::numeric_limits<double>::infinity(), 1.0}),
                 std::invalid_argument);
    EXPECT_THROW((dts::Triangle{std::numeric_limits<double>::infinity(), 1.0, 1.0}),
                 std::invalid_argument);

    EXPECT_THROW((dts::Triangle{1.0, 1.0, std::numeric_limits<double>::quiet_NaN()}),
                 std::invalid_argument);
    EXPECT_THROW((dts::Triangle{1.0, std::numeric_limits<double>::quiet_NaN(), 1.0}),
                 std::invalid_argument);
    EXPECT_THROW((dts::Triangle{std::numeric_limits<double>::quiet_NaN(), 1.0, 1.0}),
                 std::invalid_argument);

    EXPECT_THROW((dts::Triangle{1.0, 1.0, std::numeric_limits<double>::signaling_NaN()}),
                 std::invalid_argument);
    EXPECT_THROW((dts::Triangle{1.0, std::numeric_limits<double>::signaling_NaN(), 1.0}),
                 std::invalid_argument);
    EXPECT_THROW((dts::Triangle{std::numeric_limits<double>::signaling_NaN(), 1.0, 1.0}),
                 std::invalid_argument);

    EXPECT_THROW((dts::Triangle{1.0, 1.0, -42.0}), std::invalid_argument);
    EXPECT_THROW((dts::Triangle{1.0, -42.0, 1.0}), std::invalid_argument);
    EXPECT_THROW((dts::Triangle{-42.0, 1.0, 1.0}), std::invalid_argument);
}

TEST(Triangle, ConstructorThrowsOnSidesThatDontFormATriangle) {
    EXPECT_THROW((dts::Triangle{1.0, 1.0, 3.0}), std::invalid_argument);
    EXPECT_THROW((dts::Triangle{1.0, 3.0, 1.0}), std::invalid_argument);
    EXPECT_THROW((dts::Triangle{3.0, 1.0, 1.0}), std::invalid_argument);
}

TEST(Triangle, Perimeter) {
    // Assign
    const dts::Triangle circle{3.0, 4.0, 5.0};

    // Act
    const auto perimeter = circle.perimeter();

    // Assert
    EXPECT_DOUBLE_EQ(perimeter, 12.0);
}

TEST(Triangle, Area) {
    // Assign
    const dts::Triangle triangle{3.0, 4.0, 5.0};

    // Act
    const auto area = triangle.area();

    // Assert
    EXPECT_DOUBLE_EQ(area, 6.0);
}
