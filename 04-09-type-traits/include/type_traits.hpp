#ifndef INCLUDE_TYPE_TRAITS_HPP
#define INCLUDE_TYPE_TRAITS_HPP

#include <type_traits>

// -------------------------------------------------------------------------------------------------

namespace dts {

namespace detail {

template <typename T>
std::true_type test(int T::*);

template <typename>
std::false_type test(...);

} // namespace detail

template <typename T>
struct is_class_or_union : public decltype(detail::test<T>(nullptr)) {};

template <typename T>
constexpr bool is_class_or_union_v = is_class_or_union<T>::value;

} // namespace dts

// -------------------------------------------------------------------------------------------------

namespace dts {

template <typename T>
struct add_const {
    using type = const T;
};

template <typename T>
using add_const_t = typename add_const<T>::type;

} // namespace dts

// -------------------------------------------------------------------------------------------------

namespace dts {

template <typename T>
struct remove_const {
    using type = T;
};

template <typename T>
struct remove_const<const T> {
    using type = T;
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

} // namespace dts

// -------------------------------------------------------------------------------------------------

namespace dts {

namespace detail {

template <typename T>
struct decay_selector
    : public std::conditional_t<std::is_const_v<const T>, std::remove_cv<T>, std::add_pointer<T>> {
};

template <typename T, std::size_t N>
struct decay_selector<T[N]> {
    using type = T *;
};

template <typename T>
struct decay_selector<T[]> {
    using type = T *;
};

template <typename T>
using decay_selector_t = typename decay_selector<T>::type;

} // namespace detail

template <typename T>
struct decay {
    using type = detail::decay_selector_t<T>;
};

template <typename T>
struct decay<T &> {
    using type = detail::decay_selector_t<T>;
};

template <typename T>
struct decay<T &&> {
    using type = detail::decay_selector_t<T>;
};

template <typename T>
using decay_t = typename decay<T>::type;

} // namespace dts

// -------------------------------------------------------------------------------------------------

namespace dts {

template <bool C, typename T, typename F>
struct conditional {
    using type = F;
};

template <typename T, typename F>
struct conditional<true, T, F> {
    using type = T;
};

template <bool C, typename T, typename F>
using conditional_t = typename conditional<C, T, F>::type;

} // namespace dts

// -------------------------------------------------------------------------------------------------

#endif // INCLUDE_TYPE_TRAITS_HPP
