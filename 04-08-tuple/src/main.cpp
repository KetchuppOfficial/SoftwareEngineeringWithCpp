#include "tuple.hpp"

struct Point {
    int x;
    int y;

    constexpr bool operator==(const Point &) const = default;
};

int main() {
    constexpr dts::Tuple<> kEmptyTuple;
    constexpr dts::Tuple<int, double, Point> kTuple{1, 3.14, Point{3, 4}};

    static_assert(kEmptyTuple.size() == 0);
    static_assert(kTuple.size() == 3);

    static_assert(kTuple.get<0>() == 1);
    static_assert(kTuple.get<1>() == 3.14);
    static_assert(kTuple.get<2>() == Point{3, 4});
}
