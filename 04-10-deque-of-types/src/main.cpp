#include "deque_of_types.hpp"

int main() {
    static_assert(dts::size_v<dts::Deque<>> == 0 && dts::is_empty_v<dts::Deque<>> == 1);
    static_assert(dts::size_v<dts::Deque<int>> == 1 && dts::is_empty_v<dts::Deque<int>> == 0);

    static_assert(std::is_same_v<dts::front<dts::Deque<int>>, int>);
    static_assert(std::is_same_v<dts::push_front<int, dts::Deque<int>>, dts::Deque<int, int>>);
    static_assert(std::is_same_v<dts::pop_front<dts::Deque<int>>, dts::Deque<>>);

    static_assert(std::is_same_v<int, dts::back<dts::Deque<int>>>);
    static_assert(std::is_same_v<dts::Deque<int, int>, dts::push_back<int, dts::Deque<int>>>);
    static_assert(std::is_same_v<dts::Deque<>, dts::pop_back<dts::Deque<int>>>);

    static_assert(std::is_same_v<int, dts::deque_element<0, dts::Deque<int, int>>>);
    static_assert(std::is_same_v<int, dts::deque_element<1, dts::Deque<int, int>>>);

    static_assert(std::is_same_v<unsigned char, dts::max_type<dts::Deque<>>>);
    static_assert(std::is_same_v<double, dts::max_type<dts::Deque<int, double>>>);

    static_assert(!dts::has_v<int, dts::Deque<>>);
    static_assert(dts::has_v<int, dts::Deque<int>>);
    static_assert(!dts::has_v<int, dts::Deque<const int>>);
    static_assert(dts::has_v<int, dts::Deque<float, double, char, short, long, int>>);
    static_assert(!dts::has_v<int, dts::Deque<float, double, char, short, long, long long>>);
}
