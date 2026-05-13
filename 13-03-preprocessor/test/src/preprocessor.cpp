#include <gtest/gtest.h>

#include "preprocessor.hpp"

TEST(Preprocessor, Combined) {
    // Assign
    const std::string input = R"(#include <iostream>

int main(/*void*/) {
    std::cout << "Hello, World" << '\n'; // Magic!
}

)";

    // Act
    const auto output = dts::preprocess(input);

    // Assert
    EXPECT_EQ(output, R"(#include <iostream>
int main() {
    std::cout << "Hello, World" << '\n'; 
}
)");
}
