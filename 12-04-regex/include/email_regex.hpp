#ifndef INCLUDE_EMAIL_REGEX_HPP
#define INCLUDE_EMAIL_REGEX_HPP

#include <algorithm>
#include <cassert>
#include <concepts>
#include <iterator>
#include <regex>
#include <type_traits>
#include <utility>

namespace dts {

template <std::bidirectional_iterator InputIt, typename OutputIt>
    requires std::same_as<char, std::remove_const_t<std::iter_value_t<InputIt>>> &&
             std::indirectly_writable<OutputIt, std::pair<std::string, std::string>>
OutputIt find_emails_and_domains(InputIt first, InputIt last, OutputIt dest) {
    static const std::regex regex{R"([a-zA-Z0-9._%+-]+@([a-zA-Z0-9.-]+\.[a-zA-Z]{2,}))"};

    auto begin = std::regex_iterator<InputIt>{first, last, regex};
    auto end = std::regex_iterator<InputIt>{};

    return std::transform(begin, end, dest, [](const auto &match) static {
        assert(match.size() == 2);
        return std::pair{match[0], match[1]};
    });
}

} // namespace dts

#endif // INCLUDE_EMAIL_REGEX_HPP
