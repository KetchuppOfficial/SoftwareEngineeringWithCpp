#ifndef INCLUDE_FIBONACCI_ITERATOR_HPP
#define INCLUDE_FIBONACCI_ITERATOR_HPP

#include <iterator>
#include <utility>

namespace dts {

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

static_assert(std::forward_iterator<FibonacciIterator>);

} // namespace dts

#endif // INCLUDE_FIBONACCI_ITERATOR_HPP
