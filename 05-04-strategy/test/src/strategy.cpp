#include <gtest/gtest.h>

#include "entity.hpp"
#include "strategies.hpp"

TEST(DecimalStrategy, Success) {
    // Assign
    const dts::Entity<dts::DecimalStrategy> dec{42};

    // Act
    const auto result = dec.convert();

    // Assert
    EXPECT_EQ(result, "42");
}

TEST(HexStrategy, Success) {
    // Assign
    const dts::Entity<dts::HexStrategy> hex{0x42};

    // Act
    const auto result = hex.convert();

    // Assert
    EXPECT_EQ(result, "0x42");
}
