#include <numeric>

#include <gtest/gtest.h>

#include "gcd.hpp"

TEST(gcd, one_positive_one_zero_iterative) {
    // Assign
    const int x = 698917;
    const int y = 0;

    // Act & Assert
    EXPECT_EQ(dts::gcd(x, y), std::gcd(x, y));
    EXPECT_EQ(dts::gcd(y, x), std::gcd(y, x));
}

TEST(gcd, one_positive_one_zero_recursive) {
    // Assign
    const int x = 698917;
    const int y = 0;

    // Act & Assert
    EXPECT_EQ(dts::gcd(x, y, dts::recursive), std::gcd(x, y));
    EXPECT_EQ(dts::gcd(y, x, dts::recursive), std::gcd(y, x));
}

TEST(gcd, one_negative_one_zero_iterative) {
    // Assign
    const int x = 698917;
    const int y = 0;

    // Act & Assert
    EXPECT_EQ(dts::gcd(x, y), std::gcd(x, y));
    EXPECT_EQ(dts::gcd(y, x), std::gcd(y, x));
}

TEST(gcd, one_negative_one_zero_recursive) {
    // Assign
    const int x = 698917;
    const int y = 0;

    // Act & Assert
    EXPECT_EQ(dts::gcd(x, y, dts::recursive), std::gcd(x, y));
    EXPECT_EQ(dts::gcd(y, x, dts::recursive), std::gcd(y, x));
}

TEST(gcd, one_positive_one_negative_iterative) {
    // Assign
    const int x = 698917;
    const int y = -102089;

    // Act & Assert
    EXPECT_EQ(dts::gcd(x, y), std::gcd(x, y));
    EXPECT_EQ(dts::gcd(y, x), std::gcd(y, x));
}

TEST(gcd, one_positive_one_negative_recursive) {
    // Assign
    const int x = 698917;
    const int y = -102089;

    // Act & Assert
    EXPECT_EQ(dts::gcd(x, y, dts::recursive), std::gcd(x, y));
    EXPECT_EQ(dts::gcd(y, x, dts::recursive), std::gcd(y, x));
}

TEST(gcd, both_positive_iterative) {
    // Assign
    const int x = 698917;
    const int y = 102089;

    // Act & Assert
    EXPECT_EQ(dts::gcd(x, y), std::gcd(x, y));
    EXPECT_EQ(dts::gcd(y, x), std::gcd(y, x));
}

TEST(gcd, both_positive_recursive) {
    // Assign
    const int x = 698917;
    const int y = 102089;

    // Act & Assert
    EXPECT_EQ(dts::gcd(x, y, dts::recursive), std::gcd(x, y));
    EXPECT_EQ(dts::gcd(y, x, dts::recursive), std::gcd(y, x));
}

TEST(gcd, both_negative_iterative) {
    // Assign
    const int x = -698917;
    const int y = -102089;

    // Act & Assert
    EXPECT_EQ(dts::gcd(x, y), std::gcd(x, y));
    EXPECT_EQ(dts::gcd(y, x), std::gcd(y, x));
}

TEST(gcd, both_negative_recursive) {
    // Assign
    const int x = -698917;
    const int y = -102089;

    // Act & Assert
    EXPECT_EQ(dts::gcd(x, y, dts::recursive), std::gcd(x, y));
    EXPECT_EQ(dts::gcd(y, x, dts::recursive), std::gcd(y, x));
}
