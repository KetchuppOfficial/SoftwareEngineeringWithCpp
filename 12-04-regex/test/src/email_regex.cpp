#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "email_regex.hpp"

using namespace std::string_view_literals;
using Vector = std::vector<std::pair<std::string, std::string>>;

TEST(EmailRegex, NoMatch) {
    // Assign
    constexpr auto kInput = "Hello, World!"sv;
    Vector results;

    // Act
    dts::find_emails_and_domains(kInput.begin(), kInput.end(), std::back_inserter(results));

    // Assert
    EXPECT_TRUE(results.empty());
}

TEST(EmailRegex, SingleMatch) {
    // Assign
    constexpr auto kInput = "lorem info@mipt.ru ipsum"sv;
    Vector results;

    // Act
    dts::find_emails_and_domains(kInput.begin(), kInput.end(), std::back_inserter(results));

    // Assert
    EXPECT_EQ(results, (Vector{{"info@mipt.ru", "mipt.ru"}}));
}

TEST(EmailRegex, TwoMatches) {
    // Assign
    constexpr auto kInput = "My email is dolgov04@list.ru. Address of MIPT is info@mipt.ru"sv;
    Vector results;

    // Act
    dts::find_emails_and_domains(kInput.begin(), kInput.end(), std::back_inserter(results));

    // Assert
    EXPECT_EQ(results, (Vector{{"dolgov04@list.ru", "list.ru"}, {"info@mipt.ru", "mipt.ru"}}));
}
