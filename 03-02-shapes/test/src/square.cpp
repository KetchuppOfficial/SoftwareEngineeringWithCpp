#include <limits>

#include <gtest/gtest.h>

#include "square.hpp"

TEST(Square, ConstructorThrowsOnInvalidSide) {
    EXPECT_THROW(dts::Square{std::numeric_limits<double>::infinity()}, std::invalid_argument);
    EXPECT_THROW(dts::Square{std::numeric_limits<double>::quiet_NaN()}, std::invalid_argument);
    EXPECT_THROW(dts::Square{std::numeric_limits<double>::signaling_NaN()}, std::invalid_argument);
    EXPECT_THROW(dts::Square{-42.0}, std::invalid_argument);
}

TEST(Square, Perimeter) {
    // Assign
    constexpr double a = 5.0;
    const dts::Square square{a};

    // Act
    const auto perimeter = square.perimeter();

    // Assert
    EXPECT_DOUBLE_EQ(perimeter, 20.0);
}

TEST(Square, Area) {
    // Assign
    constexpr double a = 5.0;
    const dts::Square square{a};

    // Act
    const auto area = square.area();

    // Assert
    EXPECT_DOUBLE_EQ(area, 25.0);
}
