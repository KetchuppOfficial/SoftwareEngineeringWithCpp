#ifndef INCLUDE_RECURSIVE_HPP
#define INCLUDE_RECURSIVE_HPP

namespace dts {

struct recursive_t {
    explicit recursive_t() = default;
};

constexpr inline recursive_t recursive{};

} // namespace dts

#endif // INCLUDE_RECURSIVE_HPP
