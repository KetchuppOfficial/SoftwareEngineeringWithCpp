#include <numeric>

#include <gtest/gtest.h>

#include "lcm.hpp"

TEST(lcm, both_zero_iterative) {
    // Assign & Act & Assert
    EXPECT_EQ(dts::lcm(0, 0), std::lcm(0, 0));
}

TEST(lcm, both_zero_recursive) {
    // Assign & Act & Assert
    EXPECT_EQ(dts::lcm(0, 0, dts::recursive), std::lcm(0, 0));
}

TEST(lcm, one_positive_one_zero_iterative) {
    // Assign
    const int x = 25;
    const int y = 0;

    // Assert
    EXPECT_EQ(dts::lcm(x, y), std::lcm(x, y));
    EXPECT_EQ(dts::lcm(y, x), std::lcm(y, x));
}

TEST(lcm, one_positive_one_zero_recursive) {
    // Assign
    const int x = 25;
    const int y = 0;

    // Assert
    EXPECT_EQ(dts::lcm(x, y, dts::recursive), std::lcm(x, y));
    EXPECT_EQ(dts::lcm(y, x, dts::recursive), std::lcm(y, x));
}

TEST(lcm, one_negative_one_zero_iterative) {
    // Assign
    const int x = -25;
    const int y = 0;

    // Assert
    EXPECT_EQ(dts::lcm(x, y), std::lcm(x, y));
    EXPECT_EQ(dts::lcm(y, x), std::lcm(y, x));
}

TEST(lcm, one_negative_one_zero_recursive) {
    // Assign
    const int x = -25;
    const int y = 0;

    // Assert
    EXPECT_EQ(dts::lcm(x, y, dts::recursive), std::lcm(x, y));
    EXPECT_EQ(dts::lcm(y, x, dts::recursive), std::lcm(y, x));
}

TEST(lcm, one_positive_one_negative_iterative) {
    // Assign
    const int x = 25;
    const int y = -15;

    // Assert
    EXPECT_EQ(dts::lcm(x, y), std::lcm(x, y));
    EXPECT_EQ(dts::lcm(y, x), std::lcm(y, x));
}

TEST(lcm, one_positive_one_negative_recursive) {
    // Assign
    const int x = 25;
    const int y = -15;

    // Assert
    EXPECT_EQ(dts::lcm(x, y, dts::recursive), std::lcm(x, y));
    EXPECT_EQ(dts::lcm(y, x, dts::recursive), std::lcm(y, x));
}

TEST(lcm, both_positive_iterative) {
    // Assign
    const int x = 25;
    const int y = 15;

    // Assert
    EXPECT_EQ(dts::lcm(x, y), std::lcm(x, y));
    EXPECT_EQ(dts::lcm(y, x), std::lcm(y, x));
}

TEST(lcm, both_positive_recursive) {
    // Assign
    const int x = 25;
    const int y = 15;

    // Assert
    EXPECT_EQ(dts::lcm(x, y, dts::recursive), std::lcm(x, y));
    EXPECT_EQ(dts::lcm(y, x, dts::recursive), std::lcm(y, x));
}

TEST(lcm, both_negative_iterative) {
    // Assign
    const int x = -25;
    const int y = -15;

    // Assert
    EXPECT_EQ(dts::lcm(x, y), std::lcm(x, y));
    EXPECT_EQ(dts::lcm(y, x), std::lcm(y, x));
}

TEST(lcm, both_negative_recursive) {
    // Assign
    const int x = -25;
    const int y = -15;

    // Assert
    EXPECT_EQ(dts::lcm(x, y, dts::recursive), std::lcm(x, y));
    EXPECT_EQ(dts::lcm(y, x, dts::recursive), std::lcm(y, x));
}
