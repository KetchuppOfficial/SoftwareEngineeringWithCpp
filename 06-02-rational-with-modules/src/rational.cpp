module rational;

import std;

namespace dts {

std::ostream &operator<<(std::ostream &os, const Rational &rational) {
    return os << rational.num_ << '/' << rational.den_;
}

std::istream &operator>>(std::istream &is, Rational &rational) {
    is >> rational.num_;

    char c{};
    is >> c;
    if (c != '/') {
        is.setstate(std::ios_base::failbit);
    }

    int den = 1; // intentionally non-zero value
    is >> den;
    if (den == 0) {
        throw std::invalid_argument{"denominator shall not be zero"};
    }
    rational.den_ = den;

    rational.reduce();

    return is;
}

} // namespace dts
