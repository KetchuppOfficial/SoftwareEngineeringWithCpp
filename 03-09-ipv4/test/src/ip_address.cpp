#include <sstream>

#include <gtest/gtest.h>

#include "ip_address.hpp"

static std::string ip_to_str(const dts::IPv4 &ip) {
    std::ostringstream oss;
    oss << ip;
    return oss.str();
}

TEST(IPv4, DefaultConstructedIsZero) {
    // Assign & Act
    const dts::IPv4 ip;

    // Assert
    EXPECT_EQ(ip_to_str(ip), "0.0.0.0");
}

TEST(IPv4, ConstructionFromAnInteger) {
    // Assign & Act
    const dts::IPv4 ip{(std::uint32_t{1} << 24) | (std::uint32_t{2} << 16) |
                       (std::uint32_t{3} << 8) | std::uint32_t{4}};

    // Assert
    EXPECT_EQ(ip_to_str(ip), "1.2.3.4");
}

TEST(IPv4, ConstructionFromFourParts) {
    // Assign & Act
    const dts::IPv4 ip{1, 2, 3, 4};

    // Assert
    EXPECT_EQ(ip_to_str(ip), "1.2.3.4");
}

TEST(IPv4, PreIncrement) {
    // Assign
    dts::IPv4 ip{1, 2, 3, 4};

    // Act
    ++ip;

    // Assert
    EXPECT_EQ(ip_to_str(ip), "1.2.3.5");
}

TEST(IPv4, PreIncrementWithOverflowOfAPart) {
    // Assign
    dts::IPv4 ip{1, 2, 3, 255};

    // Act
    ++ip;

    // Assert
    EXPECT_EQ(ip_to_str(ip), "1.2.4.0");
}

TEST(IPv4, PostIncrement) {
    // Assign
    dts::IPv4 ip{1, 2, 3, 4};

    // Act
    const auto old_ip = ip++;

    // Assert
    EXPECT_EQ(ip_to_str(old_ip), "1.2.3.4");
    EXPECT_EQ(ip_to_str(ip), "1.2.3.5");
}

TEST(IPv4, PostIncrementWithOverflowOfAPart) {
    // Assign
    dts::IPv4 ip{1, 2, 3, 255};

    // Act
    const auto old_ip = ip++;

    // Assert
    EXPECT_EQ(ip_to_str(old_ip), "1.2.3.255");
    EXPECT_EQ(ip_to_str(ip), "1.2.4.0");
}

TEST(IPv4, PreDecrement) {
    // Assign
    dts::IPv4 ip{1, 2, 3, 4};

    // Act
    --ip;

    // Assert
    EXPECT_EQ(ip_to_str(ip), "1.2.3.3");
}

TEST(IPv4, PreDecrementWithOverflowOfAPart) {
    // Assign
    dts::IPv4 ip{1, 2, 3, 0};

    // Act
    --ip;

    // Assert
    EXPECT_EQ(ip_to_str(ip), "1.2.2.255");
}

TEST(IPv4, PostDecrement) {
    // Assign
    dts::IPv4 ip{1, 2, 3, 4};

    // Act
    const auto old_ip = ip--;

    // Assert
    EXPECT_EQ(ip_to_str(old_ip), "1.2.3.4");
    EXPECT_EQ(ip_to_str(ip), "1.2.3.3");
}

TEST(IPv4, PostDecrementWithOverflowOfAPart) {
    // Assign
    dts::IPv4 ip{1, 2, 3, 0};

    // Act
    const auto old_ip = ip--;

    // Assert
    EXPECT_EQ(ip_to_str(old_ip), "1.2.3.0");
    EXPECT_EQ(ip_to_str(ip), "1.2.2.255");
}

TEST(IPv4, LessBasedOnLastPart) {
    // Assign
    const dts::IPv4 lhs{1, 2, 3, 4};
    const dts::IPv4 rhs{1, 2, 3, 5};

    // Act & Assert
    EXPECT_LT(lhs, rhs);
}

TEST(IPv4, LessBasedOnFirstPart) {
    // Assign
    const dts::IPv4 lhs{0, 2, 3, 4};
    const dts::IPv4 rhs{1, 2, 3, 4};

    // Act & Assert
    EXPECT_LT(lhs, rhs);
}

TEST(IPv4, Equal) {
    // Assign
    const dts::IPv4 lhs{1, 2, 3, 4};
    const dts::IPv4 rhs{1, 2, 3, 4};

    // Act & Assert
    EXPECT_EQ(lhs, rhs);
}

TEST(IPv4, NotEqual) {
    // Assign
    const dts::IPv4 lhs{1, 2, 3, 4};
    const dts::IPv4 rhs{1, 2, 3, 5};

    // Act & Assert
    EXPECT_NE(lhs, rhs);
}

TEST(IPv4, TryToReadARandomStringInsteadOfIPv4) {
    // Assign
    dts::IPv4 ip{42, 42, 42, 42};
    std::stringstream ss;
    ss << "lorem ipsum";

    // Act
    ss >> ip;

    // Assert
    EXPECT_TRUE(ss.fail());
    EXPECT_EQ(ip_to_str(ip), "0.0.0.0");
}

TEST(IPv4, TryToReadAPartThatIsTooBig) {
    // Assign
    dts::IPv4 ip{42, 42, 42, 42};
    std::stringstream ss;
    ss << "1.1.256.1";

    // Act
    ss >> ip;

    // Assert
    EXPECT_TRUE(ss.fail());
    EXPECT_EQ(ip_to_str(ip), "1.1.255.0"); // first two field are read, the third one is clamped,
                                           // the fourth one is set to default because an error
                                           // occurred while reading the third one
}

TEST(IPv4, TryToWithoutLastField) {
    // Assign
    dts::IPv4 ip{42, 42, 42, 42};
    std::stringstream ss;
    ss << "1.2.3.";

    // Act
    ss >> ip;

    // Assert
    EXPECT_TRUE(ss.fail());
    EXPECT_EQ(ip_to_str(ip),
              "1.2.3.0"); // first three field are read, the fourth one is set to default because an
                          // error occurred while reading it
}

TEST(IPv4, TryToWithoutLastFieldAndADot) {
    // Assign
    dts::IPv4 ip{42, 42, 42, 42};
    std::stringstream ss;
    ss << "1.2.3";

    // Act
    ss >> ip;

    // Assert
    EXPECT_TRUE(ss.fail());
    EXPECT_EQ(ip_to_str(ip),
              "1.2.3.0"); // first three field are read, the fourth one is set to default because an
                          // error occurred while reading the last dot
}

TEST(IPv4, NoDotInTheMiddle) {
    // Assign
    dts::IPv4 ip{42, 42, 42, 42};
    std::stringstream ss;
    ss << "1.2.3;4";

    // Act
    ss >> ip;

    // Assert
    EXPECT_TRUE(ss.fail());
    EXPECT_EQ(ip_to_str(ip),
              "1.2.3.0"); // first three field are read, the fourth one is set to default because an
                          // error occurred while reading the last dot
}
TEST(IPv4, SuccessfulDeserialization) {
    // Assign
    dts::IPv4 ip;
    constexpr std::string_view ip_str = "1.2.3.4";
    std::stringstream ss;
    ss << ip_str << '\n'; // '\n' is inserted so that eofbit wouldn't be set

    // Act
    ss >> ip;

    // Assert
    EXPECT_TRUE(ss.good());
    EXPECT_EQ(ip_to_str(ip), ip_str);
}
