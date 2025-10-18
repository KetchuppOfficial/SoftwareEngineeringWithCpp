#include <cassert>
#include <cstdlib>
#include <utility>

#include "gcd.hpp"

namespace dts {

namespace {

int remainder(int a, int b) {
    assert(b != 0);
    if (int r = a % b; r >= 0) {
        return r;
    } else {
        return r + std::abs(b);
    }
}

enum class Recursive { kYes, kNo };

int gcd_recursive_impl(int a, int b) {
    assert(b != 0);
    int r = remainder(a, b);
    return (r == 0) ? b : gcd_recursive_impl(b, r);
}

template <Recursive is_recursive>
int gcd_impl(int a, int b) {
    assert(a != 0 || b != 0);
    if (b == 0) {
        std::swap(a, b);
    }

    if constexpr (is_recursive == Recursive::kYes) {
        int r = remainder(a, b);
        while (r != 0) {
            a = std::exchange(b, r);
            r = remainder(a, b);
        }
        return b;
    } else {
        return gcd_recursive_impl(a, b);
    }
}

} // unnamed namespace

int gcd(int a, int b) { return gcd_impl<Recursive::kNo>(a, b); }
int gcd(int a, int b, recursive_t) { return gcd_impl<Recursive::kYes>(a, b); }

} // namespace dts
