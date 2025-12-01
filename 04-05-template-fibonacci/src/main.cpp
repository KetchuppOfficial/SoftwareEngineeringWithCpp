#include "fibonacci.hpp"

int main() {
    static_assert(dts::fib_v<0u> == 0);
    static_assert(dts::fib_v<1u> == 1);

    static_assert(dts::fib_v<13u> == 233);

#ifdef FIBONACCI_OVERFLOW
    static_assert(dts::fib_v<47u> > 0);
#endif // FIBONACCI_OVERFLOW
}
