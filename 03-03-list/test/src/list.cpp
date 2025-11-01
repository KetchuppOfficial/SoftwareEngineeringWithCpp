#include <sstream>

#include <gtest/gtest.h>

#include "list.hpp"

static std::string to_str(const dts::List &l) {
    std::ostringstream oss;
    l.show(oss);
    return oss.str();
}

TEST(List, EmptyList) {
    // Assign & Act
    dts::List l;

    // Assert
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(to_str(l), "[]");
}

TEST(List, PushBackIntoEmptyList) {
    // Assign
    dts::List l;

    // Act
    l.push_back(42);

    // Assert
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(to_str(l), "[42]");
}

TEST(List, PushFrontIntoEmptyList) {
    // Assign
    dts::List l;

    // Act
    l.push_front(42);

    // Assert
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(to_str(l), "[42]");
}

TEST(List, PushBackIntoNonEmptyList) {
    // Assign
    dts::List l;
    l.push_back(0);

    // Act
    l.push_back(42);

    // Assert
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(to_str(l), "[0, 42]");
}

TEST(List, PushFrontIntoNonEmptyList) {
    // Assign
    dts::List l;
    l.push_back(0);

    // Act
    l.push_front(42);

    // Assert
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(to_str(l), "[42, 0]");
}

TEST(List, PopFrontFromAListWithASingleElement) {
    // Assign
    dts::List l;
    l.push_back(0);

    // Act
    l.pop_front();

    // Assert
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(to_str(l), "[]");
}

TEST(List, PopBackFromAListWithASingleElement) {
    // Assign
    dts::List l;
    l.push_back(0);

    // Act
    l.pop_back();

    // Assert
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(to_str(l), "[]");
}

TEST(List, ShowRelativelyLongList) {
    // Assign
    dts::List l;
    for (int n : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
        l.push_front(n);
    }

    // Act
    const auto str = to_str(l);

    // Assert
    EXPECT_EQ(str, "[9, 8, 7, 6, 5, 4, 3, 2, 1, 0]");
}

TEST(List, GetOnEmptyList) {
    // Assign
    dts::List l;

    // Act
    auto maybe_elem = l.get();

    // Assert
    EXPECT_FALSE(maybe_elem.has_value());
}

TEST(List, GetOnListWithOneElement) {
    // Assign
    dts::List l;
    l.push_back(42);

    // Act
    auto maybe_elem = l.get();

    // Assert
    ASSERT_TRUE(maybe_elem.has_value());
    EXPECT_EQ(*maybe_elem, 42);
}

TEST(List, GetOnListWithTwoElements) {
    // Assign
    dts::List l;
    l.push_back(0);
    l.push_back(1);

    // Act
    auto maybe_elem = l.get();

    // Assert
    ASSERT_TRUE(maybe_elem.has_value());
    EXPECT_EQ(*maybe_elem, 0);
}

TEST(List, GetOnListWithEvenNumberOfElements) {
    // Assign
    dts::List l;
    for (int n : {1, 6, 2, 9, 0, 4}) {
        l.push_back(n);
    }

    // Act
    auto maybe_elem = l.get();

    // Assert
    ASSERT_TRUE(maybe_elem.has_value());
    EXPECT_EQ(*maybe_elem, 2);
}

TEST(List, GetOnListWithOddNumberOfElements) {
    // Assign
    dts::List l;
    for (int n : {1, 6, 2, 9, 0, 4, 7}) {
        l.push_back(n);
    }

    // Act
    auto maybe_elem = l.get();

    // Assert
    ASSERT_TRUE(maybe_elem.has_value());
    EXPECT_EQ(*maybe_elem, 9);
}
