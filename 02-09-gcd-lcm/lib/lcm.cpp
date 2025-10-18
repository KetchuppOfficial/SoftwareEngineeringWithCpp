#include <cstdlib>

#include "gcd.hpp"
#include "lcm.hpp"

namespace dts {

namespace {

enum class Recursive { kYes, kNo };

template <Recursive is_recursive>
int lcm_impl(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }

    const auto a_abs = std::abs(a);
    const auto b_abs = std::abs(b);

    if constexpr (is_recursive == Recursive::kYes) {
        return (a_abs / gcd(a_abs, b_abs, recursive)) * b_abs;
    } else {
        return (a_abs / gcd(a_abs, b_abs)) * b_abs;
    }
}

} // unnamed namespace

int lcm(int a, int b) { return lcm_impl<Recursive::kNo>(a, b); }
int lcm(int a, int b, recursive_t) { return lcm_impl<Recursive::kYes>(a, b); }

} // namespace dts
