#include <array>
#include <cstdint>
#include <ranges>

#include <gtest/gtest.h>

#include "bytes_to_string.hpp"

TEST(BytesToString, EmptyRange) {
    // Act
    const auto res = dts::bytes_to_hexstr(std::views::empty<std::uint8_t>);

    // Assert
    EXPECT_TRUE(res.empty());
}

TEST(BytesToString, NonEmptyRange) {
    // Assign
    constexpr std::array<std::uint8_t, 4> kArray{0xAB, 0xBC, 0xCD, 0xDE};

    // Act
    const auto res = dts::bytes_to_hexstr(kArray);

    // Assert
    EXPECT_EQ(res, "abbccdde");
}
