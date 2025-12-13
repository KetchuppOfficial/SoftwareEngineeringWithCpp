#ifndef INCLUDE_TUPLE_HPP
#define INCLUDE_TUPLE_HPP

#include <cstddef>
#include <utility>

namespace dts {

template <typename... Ts>
class Tuple {
  public:
    constexpr std::size_t size() const noexcept { return 0uz; }
};

template <typename T, typename... Ts>
class Tuple<T, Ts...> {
  public:
    constexpr Tuple(T &&x, Ts &&...xs)
        : m_head(std::forward<T>(x)), m_tail(std::forward<Ts>(xs)...) {}

    template <std::size_t I, typename Self>
    constexpr auto &&get(this Self &&self) noexcept {
        if constexpr (I == 0) {
            return std::forward_like<Self>(self.m_head);
        } else {
            return std::forward_like<Self>(self.m_tail).template get<I - 1>();
        }
    }

    constexpr std::size_t size() const noexcept { return 1 + sizeof...(Ts); }

  private:
    [[no_unique_address]] T m_head;
    [[no_unique_address]] Tuple<Ts...> m_tail;
};

} // namespace dts

#endif // INCLUDE_TUPLE_HPP
