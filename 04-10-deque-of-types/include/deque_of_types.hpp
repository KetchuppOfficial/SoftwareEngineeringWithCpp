#ifndef INCLUDE_DEQUE_OF_TYPES_HPP
#define INCLUDE_DEQUE_OF_TYPES_HPP

#include <cstddef>
#include <type_traits>

namespace dts {

template <typename... Ts>
struct Deque {};

// ------------------------------------------------------------------------------------------------

template <typename D>
struct Size;

template <typename... Ts>
struct Size<Deque<Ts...>> {
    constexpr static auto value = sizeof...(Ts);
};

template <typename D>
constexpr auto size_v = Size<D>::value;

template <typename D>
constexpr auto is_empty_v = size_v<D> == 0;

// -------------------------------------------------------------------------------------------------

template <typename D>
struct Front;

template <typename T, typename... Ts>
struct Front<Deque<T, Ts...>> {
    using type = T;
};

template <typename D>
using front = typename Front<D>::type;

// -------------------------------------------------------------------------------------------------

template <typename T, typename D>
struct PushFront;

template <typename T, typename... Ts>
struct PushFront<T, Deque<Ts...>> {
    using type = Deque<T, Ts...>;
};

template <typename T, typename D>
using push_front = typename PushFront<T, D>::type;

// -------------------------------------------------------------------------------------------------

template <typename D>
struct PopFront;

template <typename T, typename... Ts>
struct PopFront<Deque<T, Ts...>> {
    using type = Deque<Ts...>;
};

template <typename D>
using pop_front = typename PopFront<D>::type;

// -------------------------------------------------------------------------------------------------

template <typename D>
struct Back;

template <typename T>
struct Back<Deque<T>> {
    using type = T;
};

template <typename T, typename... Ts>
struct Back<Deque<T, Ts...>> {
    using type = typename Back<Deque<Ts...>>::type;
};

template <typename D>
using back = typename Back<D>::type;

// -------------------------------------------------------------------------------------------------

template <typename T, typename D, bool IsEmpty = is_empty_v<D>>
struct PushBack {
    using type = push_front<T, D>;
};

template <typename T, typename D>
struct PushBack<T, D, /*IsEmpty=*/false> {
    using type = push_front<front<D>, typename PushBack<T, pop_front<D>>::type>;
};

template <typename T, typename D>
using push_back = typename PushBack<T, D>::type;

// -------------------------------------------------------------------------------------------------

template <typename D>
struct PopBack;

template <typename T>
struct PopBack<Deque<T>> {
    using type = Deque<>;
};

template <typename T, typename... Ts>
struct PopBack<Deque<T, Ts...>> {
    using type = push_front<T, typename PopBack<Deque<Ts...>>::type>;
};

template <typename D>
using pop_back = typename PopBack<D>::type;

// -------------------------------------------------------------------------------------------------

template <std::size_t I, typename D>
struct DequeElement : public DequeElement<I - 1, pop_front<D>> {};

template <typename D>
struct DequeElement<0, D> : public Front<D> {};

template <std::size_t I, typename D>
using deque_element = typename DequeElement<I, D>::type;

// -------------------------------------------------------------------------------------------------

template <typename D, bool IsEmpty = is_empty_v<D>>
struct MaxType {
    using type = unsigned char;
};

template <typename D>
struct MaxType<D, /*IsEmpty=*/false> {
  private:
    using current = front<D>;
    using max_of_rest = typename MaxType<pop_front<D>>::type;

  public:
    using type = std::conditional_t<sizeof(max_of_rest) <= sizeof(current), current, max_of_rest>;
};

template <typename D>
using max_type = typename MaxType<D>::type;

// -------------------------------------------------------------------------------------------------

template <typename T, typename D, bool IsEmpty = is_empty_v<D>>
struct Has {
    static constexpr bool value = false;
};

template <typename T, typename D>
struct Has<T, D, /*IsEmpty=*/false> {
    static constexpr bool value = std::is_same_v<T, front<D>> || Has<T, pop_front<D>>::value;
};

template <typename T, typename D>
constexpr bool has_v = Has<T, D>::value;

// -------------------------------------------------------------------------------------------------

} // namespace dts

#endif // INCLUDE_DEQUE_OF_TYPES_HPP
