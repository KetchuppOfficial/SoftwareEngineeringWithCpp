#ifndef INCLUDE_SQUARE_HPP
#define INCLUDE_SQUARE_HPP

#include <cmath>
#include <stdexcept>

namespace dts {

class Square final {
  public:
    constexpr Square(double a) : a_{check_value(a)} {}

    constexpr double perimeter() const noexcept { return a_ * 4; }

    constexpr double area() const { return a_ * a_; }

  private:
    static constexpr double check_value(double x) {
        if (std::isinf(x) || std::isnan(x) || x < 0) {
            throw std::invalid_argument{"invalid value for the side of a square"};
        }
        return x;
    }

    double a_;
};

} // namespace dts

#endif // INCLUDE_SQUARE_HPP
