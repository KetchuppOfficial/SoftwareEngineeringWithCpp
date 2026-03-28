#include <iostream>

#include "tracer.hpp"

static unsigned factorial(unsigned n) {
    trace();
    return (n < 2) ? 1 : n * factorial(n - 1);
}

int main() {
    trace();
    constexpr unsigned kNumber = 7;
    std::println(std::cout, "{}! == {}", kNumber, [] {
        trace();
        return factorial(kNumber);
    }());
}
