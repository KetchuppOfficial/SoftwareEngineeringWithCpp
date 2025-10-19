#ifndef INCLUDE_CIRCLE_HPP
#define INCLUDE_CIRCLE_HPP

#include <cmath>
#include <numbers>
#include <stdexcept>

namespace dts {

class Circle final {
  public:
    constexpr Circle(double r) : r_{check_value(r)} {}

    constexpr double perimeter() const noexcept { return 2 * std::numbers::pi * r_; }

    constexpr double area() const { return std::numbers::pi * r_ * r_; }

  private:
    static constexpr double check_value(double x) {
        if (std::isinf(x) || std::isnan(x) || x < 0) {
            throw std::invalid_argument{"invalid value for the radius of a circle"};
        }
        return x;
    }

    double r_;
};

} // namespace dts

#endif // INCLUDE_CIRCLE_HPP
