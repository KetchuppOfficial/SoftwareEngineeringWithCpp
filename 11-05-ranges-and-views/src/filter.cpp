#include <print>
#include <ranges>
#include <vector>

int main() {
    const std::vector v(std::from_range, std::views::iota(0, 10));
    std::println("range:    {}", v);
    std::println("filtered: {}", std::views::filter(v, [](int n) static { return n % 2 == 0; }));
}
