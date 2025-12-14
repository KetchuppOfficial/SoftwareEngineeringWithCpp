#ifndef INCLUDE_TEMPLATE_RATIONAL_HPP
#define INCLUDE_TEMPLATE_RATIONAL_HPP

#include <compare>
#include <concepts>
#include <istream>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <type_traits>

namespace dts {

template <typename T>
    requires std::signed_integral<T> && (!std::same_as<std::remove_cv_t<T>, bool>)
class TRational final {
  public:
    constexpr TRational(T num = 0, T den = 1) : num_(num), den_(den) {
        if (den == 0) {
            throw std::invalid_argument{"denominator shall not be zero"};
        }
        reduce();
    }

    constexpr T numerator() const noexcept { return num_; }
    constexpr T denominator() const noexcept { return den_; }

    constexpr explicit operator double() const { return static_cast<double>(num_) / den_; }

    constexpr TRational &operator+=(const TRational &rhs) {
        const auto lcm = std::lcm(den_, rhs.den_);
        num_ = num_ * (lcm / den_) + rhs.num_ * (lcm / rhs.den_);
        den_ = lcm;

        reduce();

        return *this;
    }

    constexpr TRational &operator-=(const TRational &other) {
        return *this += TRational(-other.num_, other.den_);
    }

    constexpr TRational &operator*=(const TRational &rhs) {
        num_ *= rhs.num_;
        den_ *= rhs.den_;

        reduce();

        return *this;
    }

    constexpr TRational &operator/=(const TRational &other) {
        return *this *= TRational(other.den_, other.num_);
    }

    constexpr TRational &operator++() { return *this += 1; }
    constexpr TRational &operator--() { return *this -= 1; }

    constexpr TRational operator++(int) {
        auto old = *this;
        ++(*this);
        return old;
    }

    constexpr TRational operator--(int) {
        auto old = *this;
        --(*this);
        return old;
    }

    constexpr friend TRational operator+(const TRational &lhs, const TRational &rhs) {
        return auto{lhs} += rhs;
    }
    constexpr friend TRational operator-(const TRational &lhs, const TRational &rhs) {
        return auto{lhs} -= rhs;
    }
    constexpr friend TRational operator*(const TRational &lhs, const TRational &rhs) {
        return auto{lhs} *= rhs;
    }
    constexpr friend TRational operator/(const TRational &lhs, const TRational &rhs) {
        return auto{lhs} /= rhs;
    }

    constexpr friend bool operator==(const TRational &lhs, const TRational &rhs) {
        return lhs.num_ == rhs.num_ && lhs.den_ == rhs.den_;
    }

    constexpr friend std::strong_ordering operator<=>(const TRational &lhs, const TRational &rhs) {
        return lhs.num_ * rhs.den_ <=> rhs.num_ * lhs.den_;
    }

    friend std::ostream &operator<<(std::ostream &os, const TRational &rational) {
        return os << rational.num_ << '/' << rational.den_;
    }

    friend std::istream &operator>>(std::istream &is, TRational &rational) {
        is >> rational.num_;

        char c{};
        is >> c;
        if (c != '/') {
            is.setstate(std::ios_base::failbit);
        }

        T den = 1; // intentionally non-zero value
        is >> den;
        if (den == 0) {
            throw std::invalid_argument{"denominator shall not be zero"};
        }
        rational.den_ = den;

        rational.reduce();

        return is;
    }

  private:
    constexpr void reduce() {
        if (den_ < 0) {
            num_ = -num_;
            den_ = -den_;
        }

        const auto gcd = std::gcd(num_, den_);
        num_ /= gcd;
        den_ /= gcd;
    }

    T num_;
    T den_;
};

} // namespace dts

#endif // INCLUDE_TEMPLATE_RATIONAL_HPP
