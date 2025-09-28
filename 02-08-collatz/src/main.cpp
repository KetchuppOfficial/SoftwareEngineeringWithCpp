#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <unordered_map>
#include <vector>

class CollatzSequence final {
  public:
    using length_type = std::size_t;
    using value_type = unsigned long long;

    CollatzSequence() = default;
    explicit CollatzSequence(length_type buckets) : num_to_length_(buckets) {}

    length_type length(value_type number) {
        if (number == 0) {
            throw std::invalid_argument{"only positive numbers are accepted"};
        } else if (number == 1) {
            return 1;
        }

        if (auto it = num_to_length_.find(number); it != num_to_length_.end()) {
            return it->second;
        }

        length_type len = 1;

        for (auto n = number; n != 1; n = next(n), ++len) {
            if (auto it = num_to_length_.find(n); it != num_to_length_.end()) {
                len += it->second - 1;
                break;
            }
        }

        num_to_length_.emplace(number, len);
        return len;
    }

  private:
    static value_type next(value_type n) noexcept {
        return (n & value_type{1}) ? value_type{3} * n + value_type{1} : n / value_type{2};
    }

    std::unordered_map<unsigned long long, std::size_t> num_to_length_;
};

int main() {
    constexpr std::size_t kSequencesCount = 100;

    using pair = std::pair<CollatzSequence::value_type, CollatzSequence::length_type>;
    std::vector<pair> lengths;
    lengths.reserve(kSequencesCount);

    CollatzSequence cs{kSequencesCount};
    for (const auto n : std::views::iota(1uz, 1uz + kSequencesCount)) {
        lengths.emplace_back(n, cs.length(n));
    }

    const auto [n, length] = *std::ranges::max_element(lengths, {}, &pair::second);
    std::println(std::cout, "[{}]: {}", n, length);

    return 0;
}
