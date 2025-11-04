#include <memory>

#include <gtest/gtest.h>

#include "client.hpp"

TEST(Client, v1) {
    // Assign
    const std::unique_ptr<dts::Entity_v1> client = std::make_unique<dts::Client>();

    // Act
    const auto result = client->test();

    // Assert
    EXPECT_EQ(result, 42);
}

TEST(Client, v2) {
    // Assign
    const std::unique_ptr<dts::Entity_v2> client = std::make_unique<dts::Client>();

    // Act
    const auto result = client->test();

    // Assert
    EXPECT_EQ(result, 43);
}
