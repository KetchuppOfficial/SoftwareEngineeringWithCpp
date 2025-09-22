#include <cassert>
#include <cstdlib>
#include <iostream>

namespace {

constexpr bool char_is_in_range(char c) {
    if (c < 32) {
        return false;
    }

    if constexpr (std::numeric_limits<char>::max() > 127) {
        if (c > 127) {
            return false;
        }
    }

    return true;
}

constexpr void classify_char(char c) {
    assert(char_is_in_range(c));

    switch (c) {
    case 'a' ... 'z':
        std::cout << "lower-case letter\n";
        break;
    case '0' ... '9':
        std::cout << "decimal digit\n";
        break;
    case 'A' ... 'Z':
        std::cout << "upper-case letter\n";
        break;
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
        std::cout << "punctuation mark\n";
        break;
    default:
        std::cout << "other character\n";
    }
}

} // unnamed namespace

int main() {
    char c;
    std::cin >> c;
    if (!std::cin.good()) {
        std::cerr << "Error occurred while reading a character\n";
        return EXIT_FAILURE;
    }

    if (!char_is_in_range(c)) {
        std::cerr << "The character shall lie in range [32; 127] for it to be classified\n";
        return EXIT_FAILURE;
    }

    classify_char(c);

    return 0;
}
