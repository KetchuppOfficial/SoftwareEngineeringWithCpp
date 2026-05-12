#ifndef INCLUDE_STRING_TO_BYTES_HPP
#define INCLUDE_STRING_TO_BYTES_HPP

#include <cassert>
#include <cstdint>
#include <ranges>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace dts {

inline std::vector<std::uint8_t> hexstr_to_bytes(std::string_view str) {
    if (str.size() % 2 != 0) {
        throw std::invalid_argument{"expected a string of even size"};
    }

    if (str.empty()) {
        return {};
    }

    auto valid_char = [](char c) static {
        return ('a' <= c && c <= 'f') || ('0' <= c && c <= '9');
    };

    auto convert_char = [](char c) static -> std::uint8_t {
        if ('0' <= c && c <= '9') {
            return c - '0';
        }
        return (c - 'a') + 0xA;
    };

    std::vector<std::uint8_t> bytes;
    bytes.reserve(str.size() / 2);
    for (const std::ranges::sized_range auto pair : std::views::chunk(str, 2)) {
        const char first = pair[0];
        const char second = pair[1];
        if (!valid_char(first) || !valid_char(second)) {
            throw std::invalid_argument{"expected only lowercase letters"};
        }
        bytes.emplace_back((convert_char(first) << 4) | convert_char(second));
    }

    return bytes;
}

} // namespace dts

#endif // INCLUDE_STRING_TO_BYTES_HPP
