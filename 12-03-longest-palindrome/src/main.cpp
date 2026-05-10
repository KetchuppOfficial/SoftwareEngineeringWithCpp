#include <cstddef>
#include <ranges>
#include <string_view>
#include <vector>

static constexpr std::string_view longest_palindrome(std::string_view str) {
    if (str.empty()) {
        return {};
    }

    const auto len = str.size();

    // table[i * len + j] == true <==> str.substr(i, j - i + 1) is a palindrome
    std::vector<bool> table(len * len, false);

    for (const auto i : std::views::iota(0uz, len)) {
        table[i * len + i] = true;
    }

    std::size_t max_palindrome_begin = 0;
    std::size_t max_palindrome_len = 1;

    for (const auto i : std::views::iota(0uz, len - 1) | std::views::reverse) {
        const auto j = i + 1;
        if (str[i] == str[j]) {
            table[i * len + j] = true;
            max_palindrome_begin = i;
            max_palindrome_len = 2;
        }
    }

    for (std::size_t k = 3; k <= len; ++k) {
        for (const auto i : std::views::iota(0uz, len - k + 1) | std::views::reverse) {
            const std::size_t j = i + k - 1;
            if (str[i] == str[j] && table[(i + 1) * len + (j - 1)]) {
                table[i * len + j] = true;
                max_palindrome_begin = i;
                max_palindrome_len = k;
            }
        }
    }

    return str.substr(max_palindrome_begin, max_palindrome_len);
}

int main() {
    using namespace std::string_view_literals;

    // No adjacent equal characters -- match the first character
    static_assert(longest_palindrome("abcdefg"sv) == "a"sv);

    // Several pairs of adjacent equal characters exist -- match the first pair
    static_assert(longest_palindrome("AAbcdEEfg"sv) == "AA"sv);

    // Several 3-chars palindromes exist -- match the first one
    static_assert(longest_palindrome("ABAjkeFGFlkj"sv) == "ABA"sv);

    // Several palindromes of different length -- match the longest
    static_assert(longest_palindrome("aBBcROTORjkwRTTRkl"sv) == "ROTOR"sv);
}
