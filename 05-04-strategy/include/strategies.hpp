#ifndef INCLUDE_STRATEGIES_HPP
#define INCLUDE_STRATEGIES_HPP

#include <format>
#include <string>

namespace dts {

struct DecimalStrategy {
    std::string convert(int n) const { return std::format("{}", n); }
};

struct HexStrategy {
    std::string convert(int n) const { return std::format("{:#x}", n); }
};

} // namespace dts

#endif // INCLUDE_STRATEGIES_HPP
