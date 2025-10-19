#ifndef INCLUDE_RECTANGLE_HPP
#define INCLUDE_RECTANGLE_HPP

#include <concepts>
#include <iostream>
#include <iterator>
#include <optional>

namespace dts {

struct Point final {
    bool operator==(const Point &) const = default;

    int x;
    int y;
};

class Rectangle final {
  public:
    Rectangle(const Point &top_left, unsigned width, unsigned height) noexcept
        : top_left_{top_left}, bottom_right_{static_cast<int>(top_left.x + width),
                                             static_cast<int>(top_left.y + height)} {}

    const Point &get_top_left() const noexcept { return top_left_; }
    const Point &get_bottom_right() const noexcept { return bottom_right_; }

    unsigned height() const noexcept { return bottom_right_.y - top_left_.y; }
    unsigned width() const noexcept { return bottom_right_.x - top_left_.x; }

    unsigned area() const noexcept { return width() * height(); }

    static std::optional<Rectangle> intersection(const Rectangle &first, const Rectangle &second) {
        if (first.bottom_right_.y <= second.top_left_.y ||
            first.bottom_right_.x <= second.top_left_.x ||
            first.top_left_.y >= second.bottom_right_.y ||
            first.top_left_.x >= second.bottom_right_.x) {
            return std::nullopt;
        }

        int top_left_x = std::max(first.top_left_.x, second.top_left_.x);
        int top_left_y = std::max(first.top_left_.y, second.top_left_.y);
        int bottom_right_x = std::min(first.bottom_right_.x, second.bottom_right_.x);
        int bottom_right_y = std::min(first.bottom_right_.y, second.bottom_right_.y);

        return Rectangle{Point{top_left_x, top_left_y},
                         static_cast<unsigned>(bottom_right_x - top_left_x),
                         static_cast<unsigned>(bottom_right_y - top_left_y)};
    }

    bool operator==(const Rectangle &) const = default;

  private:
    Point top_left_;
    Point bottom_right_;
};

std::ostream &operator<<(std::ostream &os, const Rectangle &r) {
    os << "Rectangle{(" << r.get_top_left().x << ", " << r.get_top_left().y << "), " << r.width()
       << ", " << r.height() << '}';
    return os;
}

template <std::input_iterator It>
    requires std::same_as<Rectangle, std::iter_value_t<It>>
std::optional<Rectangle> intersection(It first, It last) {
    if (first == last) {
        return std::nullopt;
    }

    std::optional maybe_intersection{*first};
    for (++first; first != last; ++first) {
        std::cout << *maybe_intersection << '\n';
        maybe_intersection = Rectangle::intersection(*maybe_intersection, *first);
        if (!maybe_intersection) {
            return std::nullopt;
        }
    }

    return maybe_intersection;
}

template <std::input_iterator It>
    requires std::same_as<Rectangle, std::iter_value_t<It>>
Rectangle bounding_box(It first, It last) {
    if (first == last) {
        return {Point{0, 0}, 0, 0};
    }

    int top_left_x = first->get_top_left().x;
    int top_left_y = first->get_top_left().y;
    int bottom_right_x = first->get_bottom_right().x;
    int bottom_right_y = first->get_bottom_right().y;
    for (++first; first != last; ++first) {
        if (auto x = first->get_top_left().x; x < top_left_x) {
            top_left_x = x;
        }
        if (auto y = first->get_top_left().y; y < top_left_y) {
            top_left_y = y;
        }
        if (auto x = first->get_bottom_right().x; x > bottom_right_x) {
            bottom_right_x = x;
        }
        if (auto y = first->get_bottom_right().y; y > bottom_right_y) {
            bottom_right_y = y;
        }
    }

    return {Point{top_left_x, top_left_y}, static_cast<unsigned>(bottom_right_x - top_left_x),
            static_cast<unsigned>(bottom_right_y - top_left_y)};
}

} // namespace dts

#endif // INCLUDE_RECTANGLE_HPP
