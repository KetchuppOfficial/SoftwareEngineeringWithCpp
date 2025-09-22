#include <cassert>
#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <utility>

namespace {

enum class CharKind { kOther, kDigit, kLowerCase, kUpperCase, kPunctuation };

} // unnamed namespace

namespace std {

template <>
struct formatter<CharKind> : public formatter<string_view> {
    template <typename ParseConstexpr>
    constexpr ParseConstexpr::iterator parse(ParseConstexpr &ctx) {
        return formatter<string_view>::parse(ctx);
    }

    template <class FmtContext>
    FmtContext::iterator format(CharKind kind, FmtContext &ctx) const {
        switch (kind) {
        case CharKind::kOther:
            return formatter<string_view>::format("other character", ctx);
        case CharKind::kDigit:
            return formatter<string_view>::format("decimal digit", ctx);
        case CharKind::kLowerCase:
            return formatter<string_view>::format("lower-case letter", ctx);
        case CharKind::kUpperCase:
            return formatter<string_view>::format("upper-case letter", ctx);
        case CharKind::kPunctuation:
            return formatter<string_view>::format("punctuation mark", ctx);
        default:
            std::unreachable();
        }
    }
};

} // namespace std

namespace {

constexpr bool char_is_in_range(char c) noexcept {
    if (c < 32) {
        return false;
    }

    if constexpr (std::is_unsigned_v<char>) {
        if (c > 127) {
            return false;
        }
    }

    return true;
}

constexpr CharKind classify_char(char c) {
    assert(char_is_in_range(c));

    switch (c) {
    case '0' ... '9':
        return CharKind::kDigit;
    case 'a' ... 'z':
        return CharKind::kLowerCase;
    case 'A' ... 'Z':
        return CharKind::kUpperCase;
    case '!':
    case '\"':
    case '\'':
    case ',':
    case '-':
    case '.':
    case ':':
    case ';':
    case '?':
    case '(':
    case ')':
        return CharKind::kPunctuation;
    default:
        return CharKind::kOther;
    }
}

} // unnamed namespace

int main() {
    char c{};
    std::cin >> c;
    if (!std::cin.good()) {
        std::println(std::cerr, "Error occurred while reading a character");
        return EXIT_FAILURE;
    }

    if (!char_is_in_range(c)) {
        std::println(std::cerr,
                     "The character shall lie in range [32; 127] for it to be classified");
        return EXIT_FAILURE;
    }

    std::println(std::cout, "{}", classify_char(c));

    return 0;
}
