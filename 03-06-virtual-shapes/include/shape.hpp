#ifndef INCLUDE_SHAPE_HPP
#define INCLUDE_SHAPE_HPP

namespace dts {

class Shape {
  public:
    virtual ~Shape() = default;

    virtual double perimeter() const = 0;
    virtual double area() const = 0;
};

} // namespace dts

#endif // INCLUDE_SHAPE_HPP
