#include <array>
#include <cstdint>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "string_to_bytes.hpp"

TEST(StringToBytes, EmptyString) {
    // Act
    const auto res = dts::hexstr_to_bytes(std::string_view{});

    // Assert
    EXPECT_TRUE(res.empty());
}

TEST(StringToBytes, ThrowsOnAStringWithOddSize) {
    // Assign
    constexpr std::string_view str{"abb"};

    // Act & Assert
    EXPECT_THROW(dts::hexstr_to_bytes(str), std::invalid_argument);
}

TEST(StringToBytes, ThrowsOnAStringWithInvalidCharacters) {
    // Assign
    constexpr std::string_view str{"AB"};

    // Act & Assert
    EXPECT_THROW(dts::hexstr_to_bytes(str), std::invalid_argument);
}

TEST(StringToBytes, NonEmptyValidString) {
    // Assign
    constexpr std::string_view str{"abbccdde"};

    // Act
    const auto res = dts::hexstr_to_bytes(str);

    // Assert
    EXPECT_EQ(res, (std::vector<std::uint8_t>{0xAB, 0xBC, 0xCD, 0xDE}));
}
