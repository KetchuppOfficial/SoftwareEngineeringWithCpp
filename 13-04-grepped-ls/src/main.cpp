#include <chrono>
#include <filesystem>
#include <format>
#include <print>
#include <ranges>
#include <regex>
#include <string>

#include <CLI/CLI.hpp>

namespace fs = std::filesystem;

namespace {

char make_type(const fs::file_status &status) {
    switch (status.type()) {
    case fs::file_type::regular:
        return 'f';
    case fs::file_type::directory:
        return 'd';
    case fs::file_type::symlink:
        return 'l';
    default:
        return '?';
    }
}

std::string make_permissions(fs::perms permissions) {
    auto lambda = [permissions](fs::perms p, char perms_c) {
        return (permissions & p) == fs::perms::none ? '-' : perms_c;
    };

    return {lambda(fs::perms::owner_read, 'r'), lambda(fs::perms::owner_write, 'w'),
            lambda(fs::perms::owner_exec, 'x')};
}

std::size_t size(const fs::path &path) {
    if (!fs::is_directory(path)) {
        return 0uz;
    }

    std::ranges::view auto sizes =
        fs::recursive_directory_iterator(path) |
        std::views::filter([](const auto &entry) static { return !entry.is_directory(); }) |
        std::views::transform([](const auto &entry) static { return entry.file_size(); });

    return std::ranges::fold_left(sizes, 0uz, std::plus<>{});
}

std::string size(const fs::directory_entry &entry) {
    auto sz = [&entry] {
        if (entry.is_regular_file()) {
            return entry.file_size();
        }
        return size(entry.path());
    }();

    constexpr std::size_t kOneKb = (1uz << 10uz);
    constexpr std::string_view kSuffixes = "BKMG";

    auto i = 0uz;
    while (i < kSuffixes.size() && sz >= kOneKb) {
        sz /= kOneKb;
        ++i;
    }

    return std::format("{: >4} ({})", sz, kSuffixes[i]);
}

void show(const fs::path &path, const std::regex &regex) {
    if (!fs::is_directory(path)) {
        std::println("{} does not refer to a directory", path.native());
        return;
    }

    for (const auto &entry : fs::directory_iterator(path)) {
        const auto filename = entry.path().filename();
        if (!std::regex_match(filename.native(), regex)) {
            continue;
        }
        std::println("{} | {} | {} | {} | {}", make_type(entry.status()),
                     make_permissions(entry.status().permissions()), size(entry),
                     std::chrono::floor<std::chrono::seconds>(
                         std::chrono::file_clock::to_sys(entry.last_write_time())),
                     filename.native());
    }
}

} // unnamed namespace

int main(int argc, char **argv) {
    CLI::App app;

    fs::path path;
    app.add_option("path", path, "path to a directory")->default_val(".");

    std::string regex_str;
    app.add_option("--regex", regex_str, "regular expression to match against file names")
        ->required();

    CLI11_PARSE(app, argc, argv);

    show(path, std::regex{regex_str});
}
