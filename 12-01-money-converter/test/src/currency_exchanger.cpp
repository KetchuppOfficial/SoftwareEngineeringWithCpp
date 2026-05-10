#include <sstream>

#include <gtest/gtest.h>

#include "currency_exchanger.hpp"

static constexpr long double kExchangeRate = 74.3; // as of 10.05.2026

class ConvertRublesToDollars : public ::testing::Test {
  protected:
    ConvertRublesToDollars() {
        iss.imbue(std::locale("ru_RU.utf8"));
        oss.imbue(std::locale("en_US.utf8"));
    }

    std::istringstream iss;
    std::ostringstream oss;
};

TEST_F(ConvertRublesToDollars, RubleSignBefore) {
    // Assign
    iss.str("₽ 371,52");

    // Act
    EXPECT_THROW(dts::convert_rubles_to_dollars(iss, oss, kExchangeRate), std::runtime_error);
}

TEST_F(ConvertRublesToDollars, RubleSignAfter) {
    // Assign
    iss.str("371,52 ₽");

    // Act
    dts::convert_rubles_to_dollars(iss, oss, kExchangeRate);

    // Assert
    EXPECT_EQ(oss.view(), "$5.00");
}
