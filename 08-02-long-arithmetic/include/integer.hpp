#ifndef INCLUDE_INTEGER_HPP
#define INCLUDE_INTEGER_HPP

#include <cassert>
#include <cctype>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <format>
#include <istream>
#include <limits>
#include <numeric>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace dts {

class Integer final {
  public:
    using digit_t = long long int;

    Integer() : m_is_negative{false}, m_digits(kSize, 0), m_size{1} {}

    Integer(digit_t digit) : m_is_negative{digit < 0}, m_digits(kSize, 0), m_size{1} {
        m_digits.front() = digit;
    }

    Integer(const std::string &str) : Integer{static_cast<std::string_view>(str)} {}

    /*
     * 12334456789123456789123456789
     * ^                            ^
     * 0                      string.size()
     */
    Integer(std::string_view string)
        : m_is_negative{string.front() == '-'}, m_digits(kSize, 0), m_size{0} {
        for (auto last = std::ssize(string) - 1; last >= 0; last -= kStep) {
            auto begin = std::max(0l, last - kStep + 1);

            if (begin == 0 && !std::isdigit(string.front())) {
                ++begin;
            }

            if (const auto digit_sv = string.substr(begin, last - begin + 1); digit_sv.size() > 0) {
                digit_t digit;
                const char *end = digit_sv.data() + digit_sv.size();
                const auto [ptr, ec] = std::from_chars(digit_sv.data(), end, digit);
                assert(ec != std::errc::result_out_of_range);
                if (ec == std::errc::invalid_argument || ptr != end) {
                    throw std::invalid_argument{"could not parse a number"};
                }
                m_digits[m_size++] = digit;
            }
        }

        reduce();
    }

    void swap(Integer &other) noexcept {
        using std::swap;
        swap(m_is_negative, other.m_is_negative);
        swap(m_digits, other.m_digits);
        swap(m_size, other.m_size);
    }

    bool sign() const noexcept { return !m_is_negative; }

    Integer abs() const {
        auto tmp = *this;
        tmp.m_is_negative = false;
        return tmp;
    }

    Integer &operator+=(Integer other) {
        if (m_is_negative == other.m_is_negative) {
            this->add(other);
        } else if (!m_is_negative && other.m_is_negative) {
            if (this->less(other)) {
                *this = std::move(other.subtract(*this));
                m_is_negative = true;
            } else {
                this->subtract(other);
            }
        } else {
            if (this->less(other)) {
                *this = std::move(other.subtract(*this));
            } else {
                this->subtract(other);
                m_is_negative = true;
            }
        }

        return *this;
    }

    Integer &operator-=(Integer other) {
        other.m_is_negative = !other.m_is_negative;
        return *this += other;
    }

    Integer &operator*=(Integer other) {
        Integer x;

        x.m_is_negative = m_is_negative ^ other.m_is_negative;

        for (auto i = 0uz; i < m_size; ++i) {
            digit_t remainder = 0;

            for (auto j = 0uz; (j < other.m_size) || remainder; ++j) {
                x.m_digits[i + j] += m_digits[i] * other.m_digits[j] + remainder;

                remainder = x.m_digits[i + j] / s_base;

                x.m_digits[i + j] -= remainder * s_base;
            }
        }

        x.m_size = m_size + other.m_size;

        swap(x);

        reduce();

        return *this;
    }

    Integer &operator/=(Integer other) {
        Integer x;

        x.m_size = m_size;

        x.m_is_negative = m_is_negative ^ other.m_is_negative;

        other.m_is_negative = false;

        Integer current;

        for (auto i = static_cast<int>(m_size) - 1; i >= 0; --i) {
            current *= s_base;

            current.m_digits.front() = m_digits[i];

            digit_t left = 0, right = s_base, digit = 0;

            while (left <= right) {
                if (auto middle = std::midpoint(left, right); other * middle <= current) {
                    left = middle + 1;

                    digit = middle;
                } else {
                    right = middle - 1;
                }
            }

            x.m_digits[i] = digit;

            current -= other * digit;
        }

        swap(x);

        reduce();

        return *this;
    }

    Integer &operator%=(Integer other) {
        // { x == ((x / a) * a + x % a) } ==> { x % a == x - ((x / a) * a) }
        return *this -= ((*this / other) * other);
    }

    Integer &operator++() { return *this += 1; }
    Integer operator++(int) {
        auto x = *this;
        ++(*this);
        return x;
    }

    Integer &operator--() { return *this -= 1; }
    Integer operator--(int) {
        auto x = *this;
        --(*this);
        return x;
    }

    friend Integer operator+(Integer lhs, const Integer &rhs) { return std::move(lhs += rhs); }
    friend Integer operator-(Integer lhs, const Integer &rhs) { return std::move(lhs -= rhs); }
    friend Integer operator*(Integer lhs, const Integer &rhs) { return std::move(lhs *= rhs); }
    friend Integer operator/(Integer lhs, const Integer &rhs) { return std::move(lhs /= rhs); }
    friend Integer operator%(Integer lhs, const Integer &rhs) { return std::move(lhs %= rhs); }

    friend Integer pow(Integer x, unsigned n) {
        if (x < 2 || n == 1) {
            return x;
        }

        Integer acc = 1;
        while (n > 0) {
            if ((n & 0x1u) == 0x1u) {
                acc *= x;
                n -= 1;
            }
            x *= x;
            n /= 2;
        }
        return acc;
    }

    friend bool operator<(const Integer &lhs, const Integer &rhs) {
        if (lhs.m_is_negative != rhs.m_is_negative) {
            return lhs.m_is_negative;
        }

        if (lhs.m_is_negative && rhs.m_is_negative) {
            return rhs.less(lhs);
        } else {
            return lhs.less(rhs);
        }
    }

    friend bool operator>(const Integer &lhs, const Integer &rhs) { return (rhs < lhs); }
    friend bool operator<=(const Integer &lhs, const Integer &rhs) { return !(rhs < lhs); }
    friend bool operator>=(const Integer &lhs, const Integer &rhs) { return !(lhs < rhs); }

    friend bool operator==(const Integer &lhs, const Integer &rhs) {
        if (lhs.m_is_negative != rhs.m_is_negative || lhs.m_size != rhs.m_size) {
            return false;
        }

        for (auto i = 0uz; i < lhs.m_size; ++i) {
            if (lhs.m_digits[i] != rhs.m_digits[i]) {
                return false;
            }
        }

        return true;
    }

    friend std::istream &operator>>(std::istream &stream, Integer &integer) {
        std::string string;
        stream >> string;
        if (!stream.bad()) {
            integer = Integer(string);
        }
        return stream;
    }

    //  ------------------------------------------------------------------------------------------

    friend std::ostream &operator<<(std::ostream &stream, const Integer &integer) {
        if (integer.m_is_negative) {
            stream << '-';
        }

        stream << integer.m_digits[integer.m_size - 1];

        for (auto i = static_cast<int>(integer.m_size) - 2; i >= 0; --i) {
            stream << std::format("{:0>{}}", integer.m_digits[i], Integer::kStep);
        }

        return stream;
    }

    friend auto sqrt(const Integer &x) {
        Integer y;

        y.m_size = (x.m_size + 1) / 2;

        for (auto i = static_cast<int>(y.m_size) - 1; i >= 0; --i) {
            digit_t left = 0, right = Integer::s_base, digit = 0;

            while (left <= right) {
                auto middle = y.m_digits[i] = std::midpoint(left, right);

                if (y * y <= x) {
                    left = middle + 1;

                    digit = std::min(middle, Integer::s_base - 1);
                } else {
                    right = middle - 1;
                }
            }

            y.m_digits[i] = digit;
        }

        y.reduce();

        return y;
    }

    friend auto multiply(const Integer &x, const Integer &y) -> Integer {
        if (auto size = std::max(x.m_size, y.m_size); size > 1) {
            auto step = size / 2;

            Integer x1, x2;

            x1.m_size = step;

            x2.m_size = size - step;

            for (auto i = 0uz; i < step; ++i) {
                x1.m_digits[i] = x.m_digits[i];
            }

            for (auto i = step; i < size; ++i) {
                x2.m_digits[i - step] = x.m_digits[i];
            }

            Integer y1, y2;

            y1.m_size = step;

            y2.m_size = size - step;

            for (auto i = 0uz; i < step; ++i) {
                y1.m_digits[i] = y.m_digits[i];
            }

            for (auto i = step; i < size; ++i) {
                y2.m_digits[i - step] = y.m_digits[i];
            }

            auto a = multiply(x2, y2);

            auto b = multiply(x1, y1);

            auto c = multiply(x2 + x1, y2 + y1);

            Integer base = Integer::s_base;

            for (auto i = 1uz; i < step; ++i) {
                base *= Integer::s_base;
            }

            auto z = a * base * base + (c - b - a) * base + b;

            z.m_is_negative = x.m_is_negative ^ y.m_is_negative;

            return z;
        } else {
            return x * y;
        }
    }

  private:
    void reduce() {
        while (m_size > 1 && !m_digits[m_size - 1]) {
            --m_size;
        }
    }

    Integer &add(const Integer &other) {
        m_size = std::max(m_size, other.m_size);

        for (auto i = 0uz; i < m_size; ++i) {
            m_digits[i] += other.m_digits[i];

            if (m_digits[i] >= s_base) {
                m_digits[i] -= s_base;

                m_digits[i + 1]++;
            }
        }

        m_size += m_digits[m_size];

        return *this;
    }

    Integer &subtract(const Integer &other) {
        for (auto i = 0uz; i < m_size; ++i) {
            m_digits[i] -= other.m_digits[i];

            if (m_digits[i] < 0) {
                m_digits[i] += s_base;

                m_digits[i + 1]--;
            }
        }

        reduce();

        return *this;
    }

    bool less(const Integer &other) const {
        if (m_size != other.m_size) {
            return m_size < other.m_size;
        }

        for (auto i = static_cast<int>(m_size) - 1; i >= 0; --i) {
            if (m_digits[i] != other.m_digits[i]) {
                return m_digits[i] < other.m_digits[i];
            }
        }

        return false;
    }

    static constexpr std::size_t kSize = 1'000uz;
    static constexpr std::ptrdiff_t kStep = std::numeric_limits<digit_t>::digits10 / 2;
    static inline const auto s_base = static_cast<digit_t>(std::pow(10, kStep));

    bool m_is_negative;
    std::vector<digit_t> m_digits;
    std::size_t m_size;
};

} // namespace dts

#endif // INCLUDE_INTEGER_HPP
