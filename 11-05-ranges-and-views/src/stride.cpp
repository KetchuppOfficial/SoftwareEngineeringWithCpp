#include <print>
#include <ranges>

int main() {
    std::println("{}", std::views::iota(0) | std::views::stride(7) | std::views::take(10));
}
