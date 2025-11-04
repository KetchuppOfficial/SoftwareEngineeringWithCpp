#ifndef INCLUDE_TRIANGLE_HPP
#define INCLUDE_TRIANGLE_HPP

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "shape.hpp"

namespace dts {

class Triangle : public Shape {
  public:
    Triangle(double a, double b, double c)
        : a_{check_value(a)}, b_{check_value(b)}, c_{check_value(c)} {
        auto max = std::max({a, b, c});
        if (a + b + c - max <= max) {
            throw std::invalid_argument{"given values cannot represent sides of a triangle"};
        }
    }

    ~Triangle() override = default;

    double perimeter() const override final { return a_ + b_ + c_; }

    double area() const override final {
        const auto p = perimeter() / 2;
        return std::sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

  private:
    static double check_value(double x) {
        if (std::isinf(x) || std::isnan(x) || x < 0) {
            throw std::invalid_argument{"invalid value for a side of a triangle"};
        }
        return x;
    }

    double a_;
    double b_;
    double c_;
};

} // namespace dts

#endif // INCLUDE_TRIANGLE_HPP
