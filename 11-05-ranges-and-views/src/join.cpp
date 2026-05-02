#include <print>
#include <ranges>
#include <vector>

int main() {
    using namespace std::string_literals;
    const std::vector v{"hello"s, ", "s, "world"s};
    std::println("range:  {}", v);
    std::println("joined: \"{}\"", std::views::join(v) | std::ranges::to<std::string>());
}
