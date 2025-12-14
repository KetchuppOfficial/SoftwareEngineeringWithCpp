#include <gtest/gtest.h>

#include "builder.hpp"

TEST(Builder, CreateDefaultPerson) {
    // Assign
    dts::Builder builder;

    auto person = builder.get();

    // Assert
    EXPECT_TRUE(person.name.empty());
    EXPECT_EQ(person.age, 0);
    EXPECT_EQ(person.grade, 0);
}

TEST(Builder, SetName) {
    // Assign
    dts::Builder builder;

    auto person = builder.name("Alexander").get();

    // Assert
    EXPECT_EQ(person.name, "Alexander");
    EXPECT_EQ(person.age, 0);
    EXPECT_EQ(person.grade, 0);
}

TEST(Builder, SetAge) {
    // Assign
    dts::Builder builder;

    auto person = builder.age(21).get();

    // Assert
    EXPECT_TRUE(person.name.empty());
    EXPECT_EQ(person.age, 21);
    EXPECT_EQ(person.grade, 0);
}

TEST(Builder, SetGrade) {
    // Assign
    dts::Builder builder;

    auto person = builder.grade(5).get();

    // Assert
    EXPECT_TRUE(person.name.empty());
    EXPECT_EQ(person.age, 0);
    EXPECT_EQ(person.grade, 5);
}

TEST(Builder, CreateFullPerson) {
    // Assign
    dts::Builder builder;

    // Act
    auto person = builder.name("Alexander").age(21).grade(5).get();

    // Assert
    EXPECT_EQ(person.name, "Alexander");
    EXPECT_EQ(person.age, 21);
    EXPECT_EQ(person.grade, 5);
}
