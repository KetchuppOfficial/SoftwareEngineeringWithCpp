#include <algorithm>
#include <print>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> numbers{std::from_range, std::views::iota(0, 10)};
    std::println("before: {}", numbers);
    std::ranges::rotate(numbers, numbers.begin() + 3);
    std::println("after:  {}", numbers);
}
