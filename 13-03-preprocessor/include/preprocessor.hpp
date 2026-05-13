#ifndef INCLUDE_PREPROCESSOR_HPP
#define INCLUDE_PREPROCESSOR_HPP

#include <algorithm>
#include <cctype>
#include <iterator>
#include <ranges>
#include <string>

namespace dts {

inline std::string preprocess(std::string input) {
    auto find_end = [](char c, auto it, auto ite) {
        ++it;
        while (it != ite) {
            if (*it == c && (*std::prev(it) != '\\' || *std::prev(it, 2) == '\\')) {
                ++it;
                break;
            }
            ++it;
        }
        return it;
    };

    auto find_raw_string_end = [](auto it, auto ite) {
        auto delim_begin = std::next(it, 2); // skip R"
        auto open_paren = std::find(delim_begin, ite, '(');

        if (open_paren == ite) {
            return ite;
        }

        std::string end_seq;
        end_seq.push_back(')');
        end_seq.append_range(std::ranges::subrange{delim_begin, open_paren});
        end_seq.push_back('"');

        auto pos = std::search(std::next(open_paren), ite, end_seq.begin(), end_seq.end());
        if (pos == ite) {
            return ite;
        }
        return std::next(pos, end_seq.size());
    };

    for (auto it = input.begin(), ite = input.end(); it != ite;) {
        if (*it == '\'') {
            it = find_end('\'', it, ite);
        } else if (*it == 'R') {
            auto next = std::next(it);
            if (next != ite && *next == '"') {
                it = find_raw_string_end(it, ite);
            }
        } else if (*it == '"') {
            it = find_end('"', it, ite);
        } else if (*it == '\n') {
            ++it;
            if (it == ite) {
                input.erase(std::prev(it), ite);
                break;
            }
            auto remove_range_end = std::find_if(
                it, ite, [](unsigned char c) { return c == '\n' || !std::isspace(c); });
            if (remove_range_end == ite) {
                input.erase(it, ite);
                break;
            } else if (*remove_range_end == '\n') {
                it = input.erase(it, std::next(remove_range_end));
                ite = input.end();
            }
        } else if (*it != '/') {
            ++it;
        } else {
            auto next = std::next(it);
            if (next == ite) {
                break;
            }

            if (*next == '/') {
                it = input.erase(it, std::find(++next, ite, '\n'));
                ite = input.end();
            } else if (*next == '*') {
                ++next;
                while (next != ite) {
                    if (*next == '/' && *std::prev(next) == '*') {
                        ++next;
                        break;
                    }
                    ++next;
                }
                it = input.erase(it, next);
                ite = input.end();
            } else {
                it = next;
            }
        }
    }

    return input;
}

} // namespace dts

#endif // INCLUDE_PREPROCESSOR_HPP
