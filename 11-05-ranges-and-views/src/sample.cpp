#include <algorithm>
#include <print>
#include <random>
#include <vector>

int main() {
    const std::vector<int> in = {1, 2, 3, 4, 5, 6};
    std::println("before: {}", in);

    const int max = in.size() + 2;
    std::vector<int> out(max);
    auto gen = std::mt19937{std::random_device{}()};

    for (decltype(out)::difference_type n = 0; n != max; ++n) {
        std::ranges::fill(std::ranges::sample(in, out.begin(), n, gen), out.end(), 0);
        std::println("n = {}: {}", n, out);
    }
}
