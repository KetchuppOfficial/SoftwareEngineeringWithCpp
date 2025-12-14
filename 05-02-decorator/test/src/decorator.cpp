#include <memory>

#include <gtest/gtest.h>

#include "decorator.hpp"

TEST(Decorator, Placeholder) {
    // Assign
    const auto decorator = std::make_unique<dts::Decorator<dts::Placeholder>>();

    // Act
    auto str = decorator->test();

    // Assert
    EXPECT_EQ(str, "\"lorem ipsum\"");
}

TEST(Decorator, BackToTheFuture) {
    // Assign
    const auto decorator = std::make_unique<dts::Decorator<dts::BackToTheFuture>>();

    // Act
    auto str = decorator->test();

    // Assert
    EXPECT_EQ(str, "\"21.10.2015\"");
}
