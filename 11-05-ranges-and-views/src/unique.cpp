#include <vector>
#include <algorithm>
#include <print>

int main() {
    std::vector<int> numbers{7, 11, 11, 4, 7, 2, 2, 0, 42, 17, 17, 1};
    std::println("before: {}", numbers);

    auto to_remove = std::ranges::unique(numbers);
    numbers.erase(to_remove.begin(), to_remove.end());

    std::println("after:  {}", numbers);
}
