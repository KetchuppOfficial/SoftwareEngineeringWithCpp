#include <sstream>

#include <gtest/gtest.h>

#include "observer.hpp"

TEST(Observer, Basic) {
    // Assign
    std::stringstream ss;
    dts::Entity entity;
    entity.add(std::make_unique<dts::Client>(ss));
    entity.add(std::make_unique<dts::Server>(ss));

    // Act
    entity.set(42);

    // Assert
    EXPECT_EQ(ss.str(), "Client::test : x = 42\nServer::test : x = 42\n");
}
