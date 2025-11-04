#ifndef INCLUDE_SQUARE_HPP
#define INCLUDE_SQUARE_HPP

#include <cmath>
#include <stdexcept>

#include "shape.hpp"

namespace dts {

class Square final : public Shape {
  public:
    Square(double a) : a_{check_value(a)} {}

    ~Square() override = default;

    double perimeter() const override { return a_ * 4; }

    double area() const override { return a_ * a_; }

  private:
    static double check_value(double x) {
        if (std::isinf(x) || std::isnan(x) || x < 0) {
            throw std::invalid_argument{"invalid value for the side of a square"};
        }
        return x;
    }

    double a_;
};

} // namespace dts

#endif // INCLUDE_SQUARE_HPP
