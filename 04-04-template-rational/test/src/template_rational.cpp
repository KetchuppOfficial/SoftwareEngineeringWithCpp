#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "template_rational.hpp"

template <typename T>
class TRationalTest : public ::testing::Test {};

using IntegralTypes = ::testing::Types<short, int, long, long long>;

TYPED_TEST_SUITE(TRationalTest, IntegralTypes);

TYPED_TEST(TRationalTest, DefaultCtor) {
    // Assign & Act
    const dts::TRational<TypeParam> r{};

    // Assert
    EXPECT_EQ(r.numerator(), 0);
    EXPECT_EQ(r.denominator(), 1);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 0.0);
}

TYPED_TEST(TRationalTest, OneArgumentCtor) {
    // Assign & Act
    const dts::TRational<TypeParam> r{42};

    // Assert
    EXPECT_EQ(r.numerator(), 42);
    EXPECT_EQ(r.denominator(), 1);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 42.0);
}

TYPED_TEST(TRationalTest, TwoArgumentsCtor) {
    // Assign & Act
    const dts::TRational<TypeParam> r{21, 6};

    // Assert
    EXPECT_EQ(r.numerator(), 7);
    EXPECT_EQ(r.denominator(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 3.5);
}

TYPED_TEST(TRationalTest, PlusEqual) {
    // Assign
    dts::TRational<TypeParam> lhs{5, 2};
    const dts::TRational<TypeParam> rhs{7, 6};

    // Act
    lhs += rhs;

    // Assert
    EXPECT_EQ(lhs.numerator(), 11);
    EXPECT_EQ(lhs.denominator(), 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(lhs), 11.0 / 3.0);
}

TYPED_TEST(TRationalTest, Plus) {
    // Assign
    const dts::TRational<TypeParam> lhs{5, 2};
    const dts::TRational<TypeParam> rhs{7, 6};

    // Act
    const auto sum = lhs + rhs;

    // Assert
    EXPECT_EQ(sum.numerator(), 11);
    EXPECT_EQ(sum.denominator(), 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(sum), 11.0 / 3.0);
}

TYPED_TEST(TRationalTest, PreIncrement) {
    // Assign
    dts::TRational<TypeParam> r{5, 2};

    // Act
    ++r;

    // Assert
    EXPECT_EQ(r.numerator(), 7);
    EXPECT_EQ(r.denominator(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 3.5);
}

TYPED_TEST(TRationalTest, PostIncrement) {
    // Assign
    dts::TRational<TypeParam> r{5, 2};

    // Act
    const auto old = r++;

    // Assert
    EXPECT_EQ(old.numerator(), 5);
    EXPECT_EQ(old.denominator(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(old), 2.5);

    EXPECT_EQ(r.numerator(), 7);
    EXPECT_EQ(r.denominator(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 3.5);
}

TYPED_TEST(TRationalTest, MinusEqual) {
    // Assign
    dts::TRational<TypeParam> lhs{5, 2};
    const dts::TRational<TypeParam> rhs{7, 6};

    // Act
    lhs -= rhs;

    // Assert
    EXPECT_EQ(lhs.numerator(), 4);
    EXPECT_EQ(lhs.denominator(), 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(lhs), 4.0 / 3.0);
}

TYPED_TEST(TRationalTest, Minus) {
    // Assign
    const dts::TRational<TypeParam> lhs{5, 2};
    const dts::TRational<TypeParam> rhs{7, 6};

    // Act
    const auto sum = lhs - rhs;

    // Assert
    EXPECT_EQ(sum.numerator(), 4);
    EXPECT_EQ(sum.denominator(), 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(sum), 4.0 / 3.0);
}

TYPED_TEST(TRationalTest, PreDecrement) {
    // Assign
    dts::TRational<TypeParam> r{5, 2};

    // Act
    --r;

    // Assert
    EXPECT_EQ(r.numerator(), 3);
    EXPECT_EQ(r.denominator(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 1.5);
}

TYPED_TEST(TRationalTest, PostDecrement) {
    // Assign
    dts::TRational<TypeParam> r{5, 2};

    // Act
    const auto old = r--;

    // Assert
    EXPECT_EQ(old.numerator(), 5);
    EXPECT_EQ(old.denominator(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(old), 2.5);

    EXPECT_EQ(r.numerator(), 3);
    EXPECT_EQ(r.denominator(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 1.5);
}

TYPED_TEST(TRationalTest, MultiplyEqual) {
    // Assign
    dts::TRational<TypeParam> lhs{2, 3};
    const dts::TRational<TypeParam> rhs{3, 2};

    // Act
    lhs *= rhs;

    // Assert
    EXPECT_EQ(lhs.numerator(), 1);
    EXPECT_EQ(lhs.denominator(), 1);
    EXPECT_DOUBLE_EQ(static_cast<double>(lhs), 1.0);
}

TYPED_TEST(TRationalTest, Multiply) {
    // Assign
    const dts::TRational<TypeParam> lhs{2, 3};
    const dts::TRational<TypeParam> rhs{3, 2};

    // Act
    const auto prod = lhs * rhs;

    // Assert
    EXPECT_EQ(prod.numerator(), 1);
    EXPECT_EQ(prod.denominator(), 1);
    EXPECT_DOUBLE_EQ(static_cast<double>(prod), 1.0);
}

TYPED_TEST(TRationalTest, DivideEqual) {
    // Assign
    dts::TRational<TypeParam> lhs{5, 2};
    const dts::TRational<TypeParam> rhs{3, 4};

    // Act
    lhs /= rhs;

    // Assert
    EXPECT_EQ(lhs.numerator(), 10);
    EXPECT_EQ(lhs.denominator(), 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(lhs), 10.0 / 3.0);
}

TYPED_TEST(TRationalTest, Divide) {
    // Assign
    const dts::TRational<TypeParam> lhs{5, 2};
    const dts::TRational<TypeParam> rhs{3, 4};

    // Act
    const auto quot = lhs / rhs;

    // Assert
    EXPECT_EQ(quot.numerator(), 10);
    EXPECT_EQ(quot.denominator(), 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(quot), 10.0 / 3.0);
}

TYPED_TEST(TRationalTest, RelationalOperationsOnEqual) {
    // Assign
    const dts::TRational<TypeParam> lhs{5, 2};
    const dts::TRational<TypeParam> rhs{10, 4};

    // Act & Assert
    EXPECT_TRUE(lhs == rhs);
    EXPECT_TRUE(rhs == lhs);

    EXPECT_FALSE(lhs != rhs);
    EXPECT_FALSE(rhs != lhs);

    EXPECT_FALSE(lhs < rhs);
    EXPECT_FALSE(rhs < lhs);

    EXPECT_FALSE(lhs > rhs);
    EXPECT_FALSE(rhs > lhs);

    EXPECT_TRUE(lhs <= rhs);
    EXPECT_TRUE(rhs <= lhs);

    EXPECT_TRUE(lhs >= rhs);
    EXPECT_TRUE(rhs >= lhs);
}

TYPED_TEST(TRationalTest, RelationalOperationsOnUnequal) {
    // Assign
    const dts::TRational<TypeParam> lhs{5, 2};
    const dts::TRational<TypeParam> rhs{3, 4};

    // Act & Assert
    EXPECT_FALSE(lhs == rhs);
    EXPECT_FALSE(rhs == lhs);

    EXPECT_TRUE(lhs != rhs);
    EXPECT_TRUE(rhs != lhs);

    EXPECT_FALSE(lhs < rhs);
    EXPECT_TRUE(rhs < lhs);

    EXPECT_TRUE(lhs > rhs);
    EXPECT_FALSE(rhs > lhs);

    EXPECT_FALSE(lhs <= rhs);
    EXPECT_TRUE(rhs <= lhs);

    EXPECT_TRUE(lhs >= rhs);
    EXPECT_FALSE(rhs >= lhs);
}

template <typename T>
static std::string to_string(const dts::TRational<T> &r) {
    std::ostringstream oss;
    oss << r;
    return oss.str();
}

TYPED_TEST(TRationalTest, Serialization) {
    // Assign
    const dts::TRational<TypeParam> r{6, 10};

    // Act
    const auto str = to_string(r);

    // Assert
    EXPECT_EQ(str, "3/5");
}

TYPED_TEST(TRationalTest, DeserializationWithError) {
    // Assign
    std::stringstream ss;
    ss << "5a10";
    dts::TRational<TypeParam> r;

    // Act
    ss >> r;

    // Assert
    EXPECT_TRUE(ss.fail());
    EXPECT_EQ(r.numerator(), 5);
    EXPECT_EQ(r.denominator(), dts::TRational<TypeParam>{}.denominator());
}

TYPED_TEST(TRationalTest, DeserializationWithException) {
    // Assign
    std::stringstream ss;
    ss << "5/0";
    dts::TRational<TypeParam> r;

    // Act & Assert

    EXPECT_THROW(ss >> r, std::invalid_argument);
}

TYPED_TEST(TRationalTest, SuccessfulDeserialization) {
    // Assign
    std::stringstream ss;
    ss << "5/10\n";
    dts::TRational<TypeParam> r;

    // Act
    ss >> r;

    // Assert
    EXPECT_TRUE(ss.good());
    EXPECT_EQ(r.numerator(), 1);
    EXPECT_EQ(r.denominator(), 2);
}
