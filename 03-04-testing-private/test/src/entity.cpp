#include <gtest/gtest.h>

#include "entity.hpp"

TEST(Entity, v1) {
    // Assign
    const dts::Entity e;

    // Act
    const auto result = dts::Tester_v1::test(e);

    // Assert
    EXPECT_EQ(result, 0);
}

TEST(Entity, v2) {
    // Assign
    const dts::Entity e;

    // Act
    const auto result = dts::Tester_v2::test(e);

    // Assert
    EXPECT_EQ(result, 42);
}
