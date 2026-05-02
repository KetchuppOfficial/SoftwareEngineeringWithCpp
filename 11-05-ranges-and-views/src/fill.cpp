#include <algorithm>
#include <print>
#include <vector>

int main() {
    std::vector<int> numbers(10);

    std::println("before: {}", numbers);

    std::ranges::fill(std::ranges::fill(numbers.begin(), numbers.begin() + numbers.size() / 2, 42),
                      numbers.end(), 88);

    std::println("after:  {}", numbers);
}
