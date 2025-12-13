#include "type_traits.hpp"

struct S {};

union U {};

int main() {
    static_assert(dts::is_class_or_union_v<S>);
    static_assert(!dts::is_class_or_union_v<S &>);
    static_assert(!dts::is_class_or_union_v<S *>);
    static_assert(dts::is_class_or_union_v<U>);
    static_assert(!dts::is_class_or_union_v<U &>);
    static_assert(!dts::is_class_or_union_v<U *>);
    static_assert(!dts::is_class_or_union_v<int>);

    static_assert(std::is_same_v<const int, dts::add_const_t<int>>);
    static_assert(std::is_same_v<const int, dts::add_const_t<const int>>);
    static_assert(std::is_same_v<int(), dts::add_const_t<int()>>);
    static_assert(std::is_same_v<int &, dts::add_const_t<int &>>);
    static_assert(std::is_same_v<int &&, dts::add_const_t<int &&>>);

    static_assert(std::is_same_v<int, dts::remove_const_t<int>>);
    static_assert(std::is_same_v<int, dts::remove_const_t<const int>>);
    static_assert(std::is_same_v<volatile int, dts::remove_const_t<volatile int>>);
    static_assert(std::is_same_v<volatile int, dts::remove_const_t<const volatile int>>);
    static_assert(std::is_same_v<int &, dts::remove_const_t<int &>>);

    static_assert(std::is_same_v<int, dts::decay<int &>::type>);
    static_assert(std::is_same_v<int, dts::decay<const int &>::type>);
    static_assert(std::is_same_v<int, dts::decay<volatile int &>::type>);
    static_assert(std::is_same_v<int, dts::decay<const volatile int &>::type>);
    static_assert(std::is_same_v<int *, dts::decay<int[]>::type>);
    static_assert(std::is_same_v<int (*)(), dts::decay<int()>::type>);

    static_assert(std::is_same_v<int, dts::conditional_t<true, int, char>>);
    static_assert(std::is_same_v<char, dts::conditional_t<false, int, char>>);
}
