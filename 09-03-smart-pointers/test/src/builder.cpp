#include <gtest/gtest.h>

#include "builder.hpp"

TEST(Builder, Client) {
    // Assign
    const std::unique_ptr<dts::Builder> builder = std::make_unique<dts::BuilderClient>();

    // Act
    const auto entity = builder->make_entity();

    // Assert
    EXPECT_EQ(entity->x, 1);
    EXPECT_EQ(entity->y, 1);
}

TEST(Builder, Server) {
    // Assign
    const std::unique_ptr<dts::Builder> builder = std::make_unique<dts::BuilderServer>();

    // Act
    const auto entity = builder->make_entity();

    // Assert
    EXPECT_EQ(entity->x, 2);
    EXPECT_EQ(entity->y, 2);
}
