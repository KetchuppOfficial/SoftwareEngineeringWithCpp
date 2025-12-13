#include "euler.hpp"
#include "pi.hpp"

int main() {
    {
        constexpr auto kEpsilon = std::array{2.0, 1.0, 0.5, 0.1, 0.04, 0.008};

        static_assert(dts::compute_e(kEpsilon[0]) == 1);
        static_assert(dts::compute_e(kEpsilon[1]) == 1 + 1);
        static_assert(dts::compute_e(kEpsilon[2]) == 1 + 1 + 0.5);
        static_assert(dts::compute_e(kEpsilon[3]) == 1 + 1 + 0.5 + (1.0 / 6));
        static_assert(dts::compute_e(kEpsilon[4]) == 1 + 1 + 0.5 + (1.0 / 6) + (1.0 / 24));
        static_assert(dts::compute_e(kEpsilon[5]) ==
                      1 + 1 + 0.5 + (1.0 / 6) + (1.0 / 24) + (1.0 / 120));
    }

    {
        constexpr auto kEpsilon = std::array{2.0, 1.0, 0.3, 0.2, 0.14, 0.11};

        static_assert(dts::compute_pi(kEpsilon[0]) == 4);
        static_assert(dts::compute_pi(kEpsilon[1]) == 4);
        static_assert(dts::compute_pi(kEpsilon[2]) == 4 * (1 - 1.0 / 3));
        static_assert(dts::compute_pi(kEpsilon[3]) == 4 * (1 - 1.0 / 3 + 1.0 / 5));
        static_assert(dts::compute_pi(kEpsilon[4]) == 4 * (1 - 1.0 / 3 + 1.0 / 5 - 1.0 / 7));
        static_assert(dts::compute_pi(kEpsilon[5]) ==
                      4 * (1 - 1.0 / 3 + 1.0 / 5 - 1.0 / 7 + 1.0 / 9));
    }
}
