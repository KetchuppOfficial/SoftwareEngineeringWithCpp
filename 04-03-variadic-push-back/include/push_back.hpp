#ifndef INCLUDE_PUSH_BACK_HPP
#define INCLUDE_PUSH_BACK_HPP

#include <utility>

namespace dts {

namespace detail {

template <typename C, typename T>
void push_back_handle([[maybe_unused]] C &cont, [[maybe_unused]] T &&arg) { /* no-op */ }

template <typename C>
void push_back_handle(C &cont, int arg) {
    cont.push_back(arg);
}

} // namespace detail

template <typename C, typename... Args>
void push_back(C &cont, Args &&...args) {
    (::dts::detail::push_back_handle(cont, std::forward<Args>(args)), ...);
}

} // namespace dts

#endif // INCLUDE_PUSH_BACK_HPP
