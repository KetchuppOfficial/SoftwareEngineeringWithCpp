#include <limits>

#include <gtest/gtest.h>

#include "circle.hpp"

TEST(Circle, ConstructorThrowsOnInvalidRadius) {
    EXPECT_THROW(dts::Circle{std::numeric_limits<double>::infinity()}, std::invalid_argument);
    EXPECT_THROW(dts::Circle{std::numeric_limits<double>::quiet_NaN()}, std::invalid_argument);
    EXPECT_THROW(dts::Circle{std::numeric_limits<double>::signaling_NaN()}, std::invalid_argument);
    EXPECT_THROW(dts::Circle{-42.0}, std::invalid_argument);
}

TEST(Circle, Perimeter) {
    // Assign
    constexpr double r = 42.0;
    const dts::Circle circle{r};

    // Act
    const auto perimeter = circle.perimeter();

    // Assert
    EXPECT_DOUBLE_EQ(perimeter, 2 * std::numbers::pi * r);
}

TEST(Circle, Area) {
    // Assign
    constexpr double r = 42.0;
    const dts::Circle circle{r};

    // Act
    const auto area = circle.area();

    // Assert
    EXPECT_DOUBLE_EQ(area, std::numbers::pi * r * r);
}
