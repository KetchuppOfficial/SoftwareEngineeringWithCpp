#include <type_traits>

#include "compile_time_ratio.hpp"
#include "duration.hpp"

int main() {
    static_assert(std::is_same_v<dts::Ratio<11, 3>, //
                                 dts::sum<dts::Ratio<7, 6>, dts::Ratio<5, 2>>>);
    static_assert(std::is_same_v<dts::Ratio<4, 3>, //
                                 dts::sub<dts::Ratio<5, 2>, dts::Ratio<7, 6>>>);
    static_assert(std::is_same_v<dts::Ratio<1, 1>, //
                                 dts::mul<dts::Ratio<2, 3>, dts::Ratio<3, 2>>>);
    static_assert(std::is_same_v<dts::Ratio<10, 3>, //
                                 dts::div<dts::Ratio<5, 2>, dts::Ratio<3, 4>>>);

    constexpr dts::Duration<int, dts::Ratio<1, 2>> duration_1(1);
    constexpr dts::Duration<int, dts::Ratio<1, 3>> duration_2(2);
    static_assert((duration_1 + duration_2).x == 7);
    static_assert((duration_1 - duration_2).x == -1);
}
