#include <climits>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>
#include <print>
#include <random>
#include <ranges>
#include <string_view>

#include <CLI/CLI.hpp>

#include "hash.hpp"

class RandomString final {
  public:
    explicit RandomString(std::size_t length)
        : length_{length}, engine_{std::random_device{}()}, char_dist_{0, kChars.size() - 1} {}

    std::string operator()() {
        std::string str(length_, '\0');
        std::generate(str.begin(), str.end(), [&] { return kChars[char_dist_(engine_)]; });
        return str;
    }

  private:
    static constexpr std::string_view kChars =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789";

    std::size_t length_;
    std::default_random_engine engine_;
    std::uniform_int_distribution<char> char_dist_;
};

int main(int argc, char **argv) try {
    CLI::App app{
        "Tool to generate JSON with hash collisions statistics for 9 different algorithms"};

    std::size_t length{};
    app.add_option("--length", length, "Length of random strings")->required();

    std::size_t count{};
    app.add_option("--count", count, "The number of random strings")->required();

    std::filesystem::path out;
    app.add_option("-o,--output", out, "Path to the output JSON with statistics")->required();

    CLI11_PARSE(app, argc, argv);

    const auto strings = [&] {
        std::vector<std::string> strings;
        strings.reserve(count);
        std::generate_n(std::back_inserter(strings), count,
                        [random_str = RandomString{length}] mutable { return random_str(); });
        return strings;
    }();

    using enum dts::Hash::Algo;
    std::map<dts::Hash::Algo, std::map<std::size_t, std::size_t>> collisions_map;
    for (auto algo : {kRS, kJS, kPJW, kELF, kBKDR, kSDBM, kDJB, kDEK, kAP}) {
        auto &per_algo_map = collisions_map.try_emplace(algo).first->second;
        for (std::string_view str : strings) {
            auto hash = dts::Hash::operator()(str, algo);
            ++per_algo_map[hash % count];
        }
    }

    std::ofstream ofs{out};

    auto print_one_map = [&](dts::Hash::Algo algo, auto &map) {
        std::println(ofs, "    \"{}\": {{", dts::Hash::to_string_view(algo));
        for (const auto &[hash, collisions] :
             map | std::views::reverse | std::views::drop(1) | std::views::reverse) {
            std::print(ofs, "        \"{}\": {},\n", hash, collisions);
        }
        const auto &[hash, collisions] = *map.rbegin();
        std::print(ofs, "        \"{}\": {}\n    }}", hash, collisions);
    };

    ofs << "{\n";
    for (const auto &[algo, map] :
         collisions_map | std::views::reverse | std::views::drop(1) | std::views::reverse) {
        print_one_map(algo, map);
        ofs << ",\n";
    }
    const auto &[algo, map] = *collisions_map.rbegin();
    print_one_map(algo, map);
    ofs << "\n}\n";
} catch (const std::exception &e) {
    std::println(stderr, "Caught an instance of {}\nwhat(): {}", typeid(e).name(), e.what());
    return EXIT_FAILURE;
} catch (...) {
    std::println(stderr, "Caught an unknown exception");
    return EXIT_FAILURE;
}
