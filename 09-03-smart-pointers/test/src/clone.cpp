#include <gtest/gtest.h>

#include "clone.hpp"

TEST(Clone, Client) {
    // Assign
    const std::unique_ptr<const dts::Entity> entity = std::make_unique<const dts::Client>();

    // Act
    const auto copy = entity->clone();

    // Assert
    EXPECT_EQ(entity->get_value(), 42);
    EXPECT_EQ(copy->get_value(), 42);
}

TEST(Clone, Server) {
    // Assign
    const std::unique_ptr<const dts::Entity> entity = std::make_unique<const dts::Server>();

    // Act
    const auto copy = entity->clone();

    // Assert
    EXPECT_EQ(entity->get_value(), 43);
    EXPECT_EQ(copy->get_value(), 43);
}
