export module rational;

import std;

namespace dts {

export class Rational final {
  public:
    constexpr Rational(int num = 0, int den = 1) : num_(num), den_(den) {
        if (den == 0) {
            throw std::invalid_argument{"denominator shall not be zero"};
        }
        reduce();
    }

    constexpr int numerator() const noexcept { return num_; }
    constexpr int denominator() const noexcept { return den_; }

    constexpr explicit operator double() const { return static_cast<double>(num_) / den_; }

    constexpr Rational &operator+=(const Rational &rhs) {
        const auto lcm = std::lcm(den_, rhs.den_);
        num_ = num_ * (lcm / den_) + rhs.num_ * (lcm / rhs.den_);
        den_ = lcm;

        reduce();

        return *this;
    }

    constexpr Rational &operator-=(const Rational &other) {
        return *this += Rational(-other.num_, other.den_);
    }

    constexpr Rational &operator*=(const Rational &rhs) {
        num_ *= rhs.num_;
        den_ *= rhs.den_;

        reduce();

        return *this;
    }

    constexpr Rational &operator/=(const Rational &other) {
        return *this *= Rational(other.den_, other.num_);
    }

    constexpr Rational &operator++() { return *this += 1; }
    constexpr Rational &operator--() { return *this -= 1; }

    constexpr Rational operator++(int) {
        auto old = *this;
        ++(*this);
        return old;
    }

    constexpr Rational operator--(int) {
        auto old = *this;
        --(*this);
        return old;
    }

    constexpr friend Rational operator+(const Rational &lhs, const Rational &rhs) {
        return auto{lhs} += rhs;
    }
    constexpr friend Rational operator-(const Rational &lhs, const Rational &rhs) {
        return auto{lhs} -= rhs;
    }
    constexpr friend Rational operator*(const Rational &lhs, const Rational &rhs) {
        return auto{lhs} *= rhs;
    }
    constexpr friend Rational operator/(const Rational &lhs, const Rational &rhs) {
        return auto{lhs} /= rhs;
    }

    constexpr friend bool operator==(const Rational &lhs, const Rational &rhs) {
        return lhs.num_ == rhs.num_ && lhs.den_ == rhs.den_;
    }

    constexpr friend std::strong_ordering operator<=>(const Rational &lhs, const Rational &rhs) {
        return lhs.num_ * rhs.den_ <=> rhs.num_ * lhs.den_;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Rational &rational);
    friend std::istream &operator>>(std::istream &stream, Rational &rational);

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

    int num_;
    int den_;
};

} // namespace dts
