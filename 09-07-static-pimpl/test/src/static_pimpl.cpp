#include <gtest/gtest.h>

#include "static_pimpl.hpp"

TEST(StaticPimpl, DefaultConstructed) {
    // Assign
    const dts::Entity entity;

    // Act & Assert
    EXPECT_EQ(entity.test(), "42");
}

TEST(StaticPimpl, MoveConstructed) {
    // Assign
    dts::Entity other;
    const dts::Entity entity{std::move(other)};

    // Act & Assert
    EXPECT_EQ(entity.test(), "42");
}

TEST(StaticPimpl, MoveAssigned) {
    // Assign
    dts::Entity other;
    dts::Entity entity;
    entity = std::move(other);

    // Act & Assert
    EXPECT_EQ(entity.test(), "42");
}
