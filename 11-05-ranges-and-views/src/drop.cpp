#include <print>
#include <ranges>
#include <vector>

int main() {
    const std::vector v(std::from_range, std::views::iota(0, 10));
    std::println("range:   {}", v);
    std::println("dropped: {}", v | std::views::drop(2) | std::views::reverse |
                                    std::views::drop(3) | std::views::reverse);
}
