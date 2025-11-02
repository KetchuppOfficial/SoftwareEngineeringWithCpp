#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "rational.hpp"

TEST(Rational, DefaultCtor) {
    // Assign & Act
    const dts::Rational r{};

    // Assert
    EXPECT_EQ(r.numerator(), 0);
    EXPECT_EQ(r.denominator(), 1);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 0.0);
}

TEST(Rational, OneArgumentCtor) {
    // Assign & Act
    const dts::Rational r{42};

    // Assert
    EXPECT_EQ(r.numerator(), 42);
    EXPECT_EQ(r.denominator(), 1);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 42.0);
}

TEST(Rational, TwoArgumentsCtor) {
    // Assign & Act
    const dts::Rational r{21, 6};

    // Assert
    EXPECT_EQ(r.numerator(), 7);
    EXPECT_EQ(r.denominator(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 3.5);
}

TEST(Rational, PlusEqual) {
    // Assign
    dts::Rational lhs{5, 2};
    const dts::Rational rhs{7, 6};

    // Act
    lhs += rhs;

    // Assert
    EXPECT_EQ(lhs.numerator(), 11);
    EXPECT_EQ(lhs.denominator(), 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(lhs), 11.0 / 3.0);
}

TEST(Rational, Plus) {
    // Assign
    const dts::Rational lhs{5, 2};
    const dts::Rational rhs{7, 6};

    // Act
    const auto sum = lhs + rhs;

    // Assert
    EXPECT_EQ(sum.numerator(), 11);
    EXPECT_EQ(sum.denominator(), 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(sum), 11.0 / 3.0);
}

TEST(Rational, PreIncrement) {
    // Assign
    dts::Rational r{5, 2};

    // Act
    ++r;

    // Assert
    EXPECT_EQ(r.numerator(), 7);
    EXPECT_EQ(r.denominator(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 3.5);
}

TEST(Rational, PostIncrement) {
    // Assign
    dts::Rational r{5, 2};

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

TEST(Rational, MinusEqual) {
    // Assign
    dts::Rational lhs{5, 2};
    const dts::Rational rhs{7, 6};

    // Act
    lhs -= rhs;

    // Assert
    EXPECT_EQ(lhs.numerator(), 4);
    EXPECT_EQ(lhs.denominator(), 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(lhs), 4.0 / 3.0);
}

TEST(Rational, Minus) {
    // Assign
    const dts::Rational lhs{5, 2};
    const dts::Rational rhs{7, 6};

    // Act
    const auto sum = lhs - rhs;

    // Assert
    EXPECT_EQ(sum.numerator(), 4);
    EXPECT_EQ(sum.denominator(), 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(sum), 4.0 / 3.0);
}

TEST(Rational, PreDecrement) {
    // Assign
    dts::Rational r{5, 2};

    // Act
    --r;

    // Assert
    EXPECT_EQ(r.numerator(), 3);
    EXPECT_EQ(r.denominator(), 2);
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 1.5);
}

TEST(Rational, PostDecrement) {
    // Assign
    dts::Rational r{5, 2};

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

TEST(Rational, MultiplyEqual) {
    // Assign
    dts::Rational lhs{2, 3};
    const dts::Rational rhs{3, 2};

    // Act
    lhs *= rhs;

    // Assert
    EXPECT_EQ(lhs.numerator(), 1);
    EXPECT_EQ(lhs.denominator(), 1);
    EXPECT_DOUBLE_EQ(static_cast<double>(lhs), 1.0);
}

TEST(Rational, Multiply) {
    // Assign
    const dts::Rational lhs{2, 3};
    const dts::Rational rhs{3, 2};

    // Act
    const auto prod = lhs * rhs;

    // Assert
    EXPECT_EQ(prod.numerator(), 1);
    EXPECT_EQ(prod.denominator(), 1);
    EXPECT_DOUBLE_EQ(static_cast<double>(prod), 1.0);
}

TEST(Rational, DivideEqual) {
    // Assign
    dts::Rational lhs{5, 2};
    const dts::Rational rhs{3, 4};

    // Act
    lhs /= rhs;

    // Assert
    EXPECT_EQ(lhs.numerator(), 10);
    EXPECT_EQ(lhs.denominator(), 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(lhs), 10.0 / 3.0);
}

TEST(Rational, Divide) {
    // Assign
    const dts::Rational lhs{5, 2};
    const dts::Rational rhs{3, 4};

    // Act
    const auto quot = lhs / rhs;

    // Assert
    EXPECT_EQ(quot.numerator(), 10);
    EXPECT_EQ(quot.denominator(), 3);
    EXPECT_DOUBLE_EQ(static_cast<double>(quot), 10.0 / 3.0);
}

TEST(Rational, RelationalOperationsOnEqual) {
    // Assign
    const dts::Rational lhs{5, 2};
    const dts::Rational rhs{10, 4};

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

TEST(Rational, RelationalOperationsOnUnequal) {
    // Assign
    const dts::Rational lhs{5, 2};
    const dts::Rational rhs{3, 4};

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

static std::string to_string(const dts::Rational &r) {
    std::ostringstream oss;
    oss << r;
    return oss.str();
}

TEST(Rational, Serialization) {
    // Assign
    const dts::Rational r{6, 10};

    // Act
    const auto str = to_string(r);

    // Assert
    EXPECT_EQ(str, "3/5");
}

TEST(Rational, DeserializationWithError) {
    // Assign
    std::stringstream ss;
    ss << "5a10";
    dts::Rational r;

    // Act
    ss >> r;

    // Assert
    EXPECT_TRUE(ss.fail());
    EXPECT_EQ(r.numerator(), 5);
    EXPECT_EQ(r.denominator(), dts::Rational{}.denominator());
}

TEST(Rational, DeserializationWithException) {
    // Assign
    std::stringstream ss;
    ss << "5/0";
    dts::Rational r;

    // Act & Assert

    EXPECT_THROW(ss >> r, std::invalid_argument);
}

TEST(Rational, SuccessfulDeserialization) {
    // Assign
    std::stringstream ss;
    ss << "5/10\n";
    dts::Rational r;

    // Act
    ss >> r;

    // Assert
    EXPECT_TRUE(ss.good());
    EXPECT_EQ(r.numerator(), 1);
    EXPECT_EQ(r.denominator(), 2);
}
