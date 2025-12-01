#ifndef INCLUDE_FIBONACCI_HPP
#define INCLUDE_FIBONACCI_HPP

#include <limits>

namespace dts {

template <unsigned N>
struct fib {
    static_assert(fib<N - 1>::value <= std::numeric_limits<int>::max() - fib<N - 2>::value,
                  "Next Fibonacci number overflows int");

    static constexpr int value = fib<N - 1>::value + fib<N - 2>::value;
};

template <>
struct fib<1u> {
    static constexpr int value = 1;
};

template <>
struct fib<0u> {
    static constexpr int value = 0;
};

template <unsigned N>
constexpr int fib_v = fib<N>::value;

} // namespace dts

#endif // INCLUDE_FIBONACCI_HPP
