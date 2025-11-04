#ifndef INCLUDE_CIRCLE_HPP
#define INCLUDE_CIRCLE_HPP

#include <cmath>
#include <numbers>
#include <stdexcept>

#include "shape.hpp"

namespace dts {

class Circle final : public Shape {
  public:
    Circle(double r) : r_{check_value(r)} {}

    ~Circle() override = default;

    double perimeter() const override { return 2 * std::numbers::pi * r_; }

    double area() const override { return std::numbers::pi * r_ * r_; }

  private:
    static double check_value(double x) {
        if (std::isinf(x) || std::isnan(x) || x < 0) {
            throw std::invalid_argument{"invalid value for the radius of a circle"};
        }
        return x;
    }

    double r_;
};

} // namespace dts

#endif // INCLUDE_CIRCLE_HPP
