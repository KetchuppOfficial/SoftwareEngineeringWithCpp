#ifndef INCLUDE_BYTES_TO_STRING_HPP
#define INCLUDE_BYTES_TO_STRING_HPP

#include <concepts>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <iterator>
#include <ranges>
#include <sstream>
#include <string>
#include <utility>

namespace dts {

template <std::input_iterator I, std::sentinel_for<I> S>
    requires std::same_as<std::uint8_t, std::remove_const_t<std::iter_value_t<I>>>
std::string bytes_to_hexstr(I begin, S end) {
    std::ostringstream oss;

    for (; begin != end; ++begin) {
        oss << std::hex << std::setw(2) << std::setfill('0');
        oss.operator<<(*begin); // a simple hack not to write static_cast :)
    }

    return std::move(oss).str();
}

template <std::ranges::input_range R>
    requires std::same_as<std::uint8_t, std::remove_const_t<std::ranges::range_value_t<R>>>
std::string bytes_to_hexstr(R &&r) {
    return bytes_to_hexstr(std::ranges::begin(r), std::ranges::end(r));
}

} // namespace dts

#endif // INCLUDE_BYTES_TO_STRING_HPP