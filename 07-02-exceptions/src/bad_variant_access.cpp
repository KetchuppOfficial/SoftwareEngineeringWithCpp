#include <cstdio>
#include <cstdlib>
#include <exception>
#include <variant>
#include <print>
#include <string>

int main() try {
    const std::variant<int, std::string> v{42};
    std::println("{}", std::get<std::string>(v));
} catch (const std::exception &e) {
    std::println(stderr, "Caught an instance of {}\nwhat(): {}", typeid(e).name(), e.what());
    return EXIT_FAILURE;
} catch (...) {
    std::println(stderr, "Caught an unknown exception");
    return EXIT_FAILURE;
}
