#include <algorithm>
#include <print>
#include <string>
#include <utility>
#include <vector>

int main() {
    constexpr const char *kSpecialCity = "Hiroshima";

    using pair = std::pair<std::string, unsigned>;

    std::vector<pair> cities{
        {"Moscow", 13'000'000},    {"Paris", 2'000'000},  {"New York City", 8'000'000},
        {kSpecialCity, 1'000'000}, {"London", 9'000'000},
    };

    std::println("before 1945: {}", cities);

    // Sorry for this
    std::ranges::replace(cities, kSpecialCity, pair{kSpecialCity, 0u}, &pair::first);

    std::println("after 1945:  {}", cities);
}
