#ifndef INCLUDE_ADDABLE_HPP
#define INCLUDE_ADDABLE_HPP

namespace dts {

namespace detail {

template <typename T>
struct empty_base {};

} // namespace detail

template <typename T, typename B = detail::empty_base<T>>
struct addable : B {
    constexpr friend T operator+(const T &lhs, const T &rhs) { return auto(lhs) += rhs; }
};

template <typename T, typename B = detail::empty_base<T>>
struct subtractable : B {
    constexpr friend T operator-(const T &lhs, const T &rhs) { return auto(lhs) -= rhs; }
};

template <typename T, typename B = detail::empty_base<T>>
struct multipliable : B {
    constexpr friend T operator*(const T &lhs, const T &rhs) { return auto(lhs) *= rhs; }
};

template <typename T, typename B = detail::empty_base<T>>
struct dividable : B {
    constexpr friend T operator/(const T &lhs, const T &rhs) { return auto(lhs) /= rhs; }
};

template <typename T, typename B = detail::empty_base<T>>
struct incrementable : B {
    constexpr friend T operator++(T &val, int) {
        auto copy(val);
        ++val;
        return copy;
    }
};

template <typename T, typename B = detail::empty_base<T>>
struct decrementable : B {
    constexpr friend T operator--(T &val, int) {
        auto copy(val);
        --val;
        return copy;
    }
};

} // namespace dts

#endif // INCLUDE_ADDABLE_HPP
