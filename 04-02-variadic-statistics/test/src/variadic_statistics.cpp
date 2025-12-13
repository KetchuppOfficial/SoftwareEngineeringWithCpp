#include <gtest/gtest.h>

#include "variadic_statistics.hpp"

TEST(VariadicMax, OneArgument) { EXPECT_EQ(42.0, dts::variadic_max(42.0)); }

TEST(VariadicMax, ManyArguments) { EXPECT_EQ(42.0, dts::variadic_max(1.0, 5.0, 2.0, 3.0, 42.0)); }

TEST(VariadicMin, OneArgument) { EXPECT_EQ(42.0, dts::variadic_min(42.0)); }

TEST(VariadicMin, ManyArguments) { EXPECT_EQ(1.0, dts::variadic_min(1.0, 5.0, 2.0, 3.0, 42.0)); }

TEST(VariadicSum, OneArgument) { EXPECT_EQ(42.0, dts::variadic_sum(42.0)); }

TEST(VariadicSum, ManyArguments) { EXPECT_EQ(10.0, dts::variadic_sum(1.0, 2.0, 3.0, 4.0)); }

TEST(VariadicMean, OneArgument) { EXPECT_EQ(42.0, dts::variadic_mean(42.0)); }

TEST(VariadicMean, ManyArguments) { EXPECT_EQ(2.5, dts::variadic_mean(1.0, 2.0, 3.0, 4.0)); }
