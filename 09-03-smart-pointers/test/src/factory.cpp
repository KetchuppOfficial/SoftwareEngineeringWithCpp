#include <gtest/gtest.h>

#include "factory.hpp"

TEST(Factory, Client) {
    // Assign
    const std::unique_ptr<dts::Factory> factory = std::make_unique<dts::FactoryClient>();

    // Act
    const auto entity = factory->make_entity();

    // Assert
    EXPECT_EQ(entity->who_am_i(), "Client");
}

TEST(Factory, Server) {
    // Assign
    const std::unique_ptr<dts::Factory> factory = std::make_unique<dts::FactoryServer>();

    // Act
    const auto entity = factory->make_entity();

    // Assert
    EXPECT_EQ(entity->who_am_i(), "Server");
}
