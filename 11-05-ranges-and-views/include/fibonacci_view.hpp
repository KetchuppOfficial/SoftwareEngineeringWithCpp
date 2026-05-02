#ifndef INCLUDE_FIBONACCI_VIEW_HPP
#define INCLUDE_FIBONACCI_VIEW_HPP

#include <ranges>

namespace dts {

namespace ranges {

class FibonacciView : public std::ranges::view_interface<FibonacciView> {
  private:
    class FibonacciIterator final {
      public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = int;
        using reference = value_type;
        using difference_type = value_type;
        using pointer = void; // compliant with std::iterator_traits default

        constexpr FibonacciIterator() noexcept : curr_{0}, next_{1} {}

        constexpr reference operator*() const noexcept { return curr_; }

        constexpr FibonacciIterator &operator++() noexcept {
            curr_ = std::exchange(next_, curr_ + next_);
            return *this;
        }

        constexpr FibonacciIterator operator++(int) noexcept {
            auto old = *this;
            ++(*this);
            return old;
        }

        constexpr bool operator==(const FibonacciIterator &) const = default;

      private:
        int curr_;
        int next_;
    };

  public:
    constexpr auto begin() const noexcept { return FibonacciIterator{}; }
    constexpr auto end() const noexcept { return std::unreachable_sentinel; }
};

namespace views {

inline constexpr FibonacciView fibonacci;

} // namespace views

} // namespace ranges

namespace views = ranges::views;

} // namespace dts

#endif // INCLUDE_FIBONACCI_VIEW_HPP
