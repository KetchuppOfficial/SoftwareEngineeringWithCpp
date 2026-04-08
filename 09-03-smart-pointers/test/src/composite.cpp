#include <gtest/gtest.h>

#include "composite.hpp"

TEST(Composite, Basic) {
    // Assign
    constexpr std::size_t kClients = 42;
    constexpr std::size_t kServers = 21;

    // Act
    const auto composite = dts::make_composite(kClients, kServers);

    // Assert
    EXPECT_EQ(composite->test(), kClients * 1 + kServers * 2);
}

TEST(Composite, CompositeOfComposites) {
    // Assign
    constexpr std::size_t kComposites = 5;
    auto composite = std::make_unique<dts::Composite>();
    for (auto _ : std::views::iota(0uz, kComposites)) {
        composite->add(dts::make_composite(1, 1));
    }
    const dts::Entity *entity = composite.get();

    // Act & Assert
    EXPECT_EQ(entity->test(), kComposites * 1 + kComposites * 2);
}
