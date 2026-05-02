#include <print>
#include <ranges>
#include <vector>

int main() {
    const std::vector v{3, 9, 11, 0, 4, 17};

    // Emulating std::views::enumerate
    for (auto [i, value] : std::views::zip(std::views::iota(0), v)) {
        std::println("v[{}] == {}", i, value);
    }
}
