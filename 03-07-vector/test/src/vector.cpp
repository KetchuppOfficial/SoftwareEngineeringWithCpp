#include <ranges>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "vector.hpp"

TEST(Vector, DefaultCtor) {
    // Assign & Act
    const dts::Vector v;

    // Assert
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(Vector, IListCtor) {
    // Assign
    auto ilist = {1, 2, 3, 4, 5};

    // Act
    const dts::Vector v{ilist};

    // Assert
    EXPECT_FALSE(v.empty());
    EXPECT_EQ(v.size(), ilist.size());
    EXPECT_GE(v.capacity(), v.size());
    EXPECT_TRUE(std::equal(v.begin(), v.end(), ilist.begin(), ilist.end()));
}

TEST(Vector, CopyConstructFromEmptyVector) {
    // Assign
    const dts::Vector v;

    // Act
    const auto copy = v;

    // Assert
    EXPECT_TRUE(copy.empty());
    EXPECT_EQ(copy.size(), 0);
    EXPECT_EQ(copy.capacity(), 0);
}

TEST(Vector, CopyConstructFromNonEmptyVector) {
    // Assign
    const dts::Vector v{1, 2, 3, 4, 5};

    // Act
    const auto copy = v;

    // Assert
    EXPECT_FALSE(copy.empty());
    EXPECT_EQ(copy.size(), v.size());
    EXPECT_GE(copy.capacity(), copy.size());
    EXPECT_TRUE(std::equal(v.begin(), v.end(), v.begin(), v.end()));
}

TEST(Vector, CopyAssignFromEmptyVectorToEmtpyVector) {
    // Assign
    dts::Vector lhs;
    const dts::Vector rhs;

    // Act
    lhs = rhs;

    // Assert
    EXPECT_TRUE(lhs.empty());
    EXPECT_EQ(lhs.size(), 0);
    EXPECT_EQ(lhs.capacity(), 0);
}

TEST(Vector, CopyAssignFromNonEmptyVectorToEmtpyVector) {
    // Assign
    dts::Vector lhs;
    const dts::Vector rhs{1, 2, 3, 4, 5};

    // Act
    lhs = rhs;

    // Assert
    EXPECT_FALSE(lhs.empty());
    EXPECT_EQ(lhs.size(), rhs.size());
    EXPECT_GE(lhs.capacity(), lhs.size());
    EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

TEST(Vector, CopyAssignFromEmptyVectorToNonEmtpyVector) {
    // Assign
    dts::Vector lhs{1, 2, 3, 4, 5};
    const dts::Vector rhs;

    // Act
    lhs = rhs;

    // Assert
    EXPECT_TRUE(lhs.empty());
    EXPECT_EQ(lhs.size(), 0);
    EXPECT_EQ(lhs.capacity(), 0);
}

TEST(Vector, CopyAssignFromNonEmptyVectorToNonEmtpyVector) {
    // Assign
    dts::Vector lhs{6, 7, 8};
    const dts::Vector rhs{1, 2, 3, 4, 5};

    // Act
    lhs = rhs;

    // Assert
    EXPECT_FALSE(lhs.empty());
    EXPECT_EQ(lhs.size(), rhs.size());
    EXPECT_GE(lhs.capacity(), lhs.size());
    EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

TEST(Vector, CopyAssignEmptyVectorToItself) {
    // Assign
    dts::Vector v;

    // Act
    v = v;

    // Assert
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(Vector, CopyAssignNonEmptyVectorToItself) {
    // Assign
    auto ilist = {1, 2, 3, 4, 5};
    dts::Vector v{ilist};

    // Act
    v = v;

    // Assert
    EXPECT_FALSE(v.empty());
    EXPECT_EQ(v.size(), ilist.size());
    EXPECT_GE(v.capacity(), v.size());
    EXPECT_TRUE(std::equal(v.begin(), v.end(), ilist.begin(), ilist.end()));
}

TEST(Vector, MoveConstructFromEmptyVector) {
    // Assign
    dts::Vector v;

    // Act
    const auto copy = std::move(v);

    // Assert
    EXPECT_TRUE(copy.empty());
    EXPECT_EQ(copy.size(), 0);
    EXPECT_EQ(copy.capacity(), 0);

    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(Vector, MoveConstructFromNonEmptyVector) {
    // Assign
    auto ilist = {1, 2, 3, 4, 5};
    dts::Vector v{ilist};

    // Act
    const auto copy = std::move(v);

    // Assert
    EXPECT_FALSE(copy.empty());
    EXPECT_EQ(copy.size(), ilist.size());
    EXPECT_GE(copy.capacity(), copy.size());

    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(Vector, MoveAssignFromEmptyVectorToEmtpyVector) {
    // Assign
    dts::Vector lhs;
    dts::Vector rhs;

    // Act
    lhs = std::move(rhs);

    // Assert
    EXPECT_TRUE(lhs.empty());
    EXPECT_EQ(lhs.size(), 0);
    EXPECT_EQ(lhs.capacity(), 0);
}

TEST(Vector, MoveAssignFromNonEmptyVectorToEmtpyVector) {
    // Assign
    auto ilist = {1, 2, 3, 4, 5};
    dts::Vector lhs;
    dts::Vector rhs{ilist};

    // Act
    lhs = std::move(rhs);

    // Assert
    EXPECT_FALSE(lhs.empty());
    EXPECT_EQ(lhs.size(), ilist.size());
    EXPECT_GE(lhs.capacity(), lhs.size());
    EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), ilist.begin(), ilist.end()));
}

TEST(Vector, MoveAssignFromEmptyVectorToNonEmtpyVector) {
    // Assign
    dts::Vector lhs{1, 2, 3, 4, 5};
    dts::Vector rhs;

    // Act
    lhs = std::move(rhs);

    // Assert
    EXPECT_TRUE(lhs.empty());
    EXPECT_EQ(lhs.size(), 0);
    EXPECT_EQ(lhs.capacity(), 0);
}

TEST(Vector, MoveAssignFromNonEmptyVectorToNonEmtpyVector) {
    // Assign
    auto ilist = {1, 2, 3, 4, 5};
    dts::Vector lhs{6, 7, 8};
    dts::Vector rhs{ilist};

    // Act
    lhs = std::move(rhs);

    // Assert
    EXPECT_FALSE(lhs.empty());
    EXPECT_EQ(lhs.size(), ilist.size());
    EXPECT_GE(lhs.capacity(), lhs.size());
    EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), ilist.begin(), ilist.end()));
}

TEST(Vector, MoveAssignEmptyVectorToItself) {
    // Assign
    dts::Vector v;

    // Act
    v = std::move(v);

    // Assert
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(Vector, MoveAssignNonEmptyVectorToItself) {
    // Assign
    auto ilist = {1, 2, 3, 4, 5};
    dts::Vector v{ilist};

    // Act
    v = std::move(v);

    // Assert
    EXPECT_FALSE(v.empty());
    EXPECT_EQ(v.size(), ilist.size());
    EXPECT_GE(v.capacity(), v.size());
    EXPECT_TRUE(std::equal(v.begin(), v.end(), ilist.begin(), ilist.end()));
}

TEST(Vector, MemberSwap) {
    // Assign
    auto ilist_1 = {1, 2, 3, 4, 5};
    auto ilist_2 = {6, 7, 8};
    dts::Vector v_1{ilist_1};
    dts::Vector v_2{ilist_2};

    // Act
    v_1.swap(v_2);

    // Assert
    EXPECT_FALSE(v_1.empty());
    EXPECT_EQ(v_1.size(), ilist_2.size());
    EXPECT_GE(v_1.capacity(), v_1.size());
    EXPECT_TRUE(std::equal(v_1.begin(), v_1.end(), ilist_2.begin(), ilist_2.end()));

    EXPECT_FALSE(v_2.empty());
    EXPECT_EQ(v_2.size(), ilist_1.size());
    EXPECT_GE(v_2.capacity(), v_2.size());
    EXPECT_TRUE(std::equal(v_2.begin(), v_2.end(), ilist_1.begin(), ilist_1.end()));
}

TEST(Vector, NonMemberSwap) {
    // Assign
    auto ilist_1 = {1, 2, 3, 4, 5};
    auto ilist_2 = {6, 7, 8};
    dts::Vector v_1{ilist_1};
    dts::Vector v_2{ilist_2};

    // Act
    swap(v_1, v_2);

    // Assert
    EXPECT_FALSE(v_1.empty());
    EXPECT_EQ(v_1.size(), ilist_2.size());
    EXPECT_GE(v_1.capacity(), v_1.size());
    EXPECT_TRUE(std::equal(v_1.begin(), v_1.end(), ilist_2.begin(), ilist_2.end()));

    EXPECT_FALSE(v_2.empty());
    EXPECT_EQ(v_2.size(), ilist_1.size());
    EXPECT_GE(v_2.capacity(), v_2.size());
    EXPECT_TRUE(std::equal(v_2.begin(), v_2.end(), ilist_1.begin(), ilist_1.end()));
}

TEST(Vector, Clear) {
    // Assign
    dts::Vector v{1, 2, 3, 4, 5};

    // Act
    v.clear();

    // Assert
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(Vector, PushBack) {
    // Assign
    dts::Vector v;
    const std::vector vec(std::from_range, std::views::iota(0, 100));

    // Act
    for (auto elem : vec) {
        v.push_back(elem);
    }

    // Assert
    EXPECT_FALSE(v.empty());
    EXPECT_EQ(v.size(), vec.size());
    EXPECT_GE(v.capacity(), v.size());
    EXPECT_TRUE(std::ranges::equal(v, vec));
}
