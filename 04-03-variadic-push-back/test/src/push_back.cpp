#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "push_back.hpp"

class PushBack : public ::testing::Test {
  protected:
    std::vector<int> vec;
};

TEST_F(PushBack, EmptyPack) {
    // Act
    dts::push_back(vec);

    // Assert
    EXPECT_TRUE(vec.empty());
}

TEST_F(PushBack, PackOfOneInt) {
    // Act
    dts::push_back(vec, 42);

    // Assert
    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.front(), 42);
}

TEST_F(PushBack, PackOfOneConstInt) {
    // Assign
    const int x = 42;

    // Act
    dts::push_back(vec, x);

    // Assert
    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.front(), 42);
}

TEST_F(PushBack, PackOfOneNonInt) {
    // Act
    dts::push_back(vec, std::string{"42"});

    // Assert
    EXPECT_TRUE(vec.empty());
}

TEST_F(PushBack, PackOfOneConstNonInt) {
    // Assign
    const std::string s{"42"};

    // Act
    dts::push_back(vec, s);

    // Assert
    EXPECT_TRUE(vec.empty());
}

TEST_F(PushBack, DiversePack) {
    // Assign
    const int x = 42;
    const std::string s{"42"};
    const std::vector result{1, 2, 3, 5, 42};

    // Act
    dts::push_back(vec, 1, 2, 3, '4', 5, 6.0, x, s);

    // Assert
    EXPECT_EQ(vec, result);
}
