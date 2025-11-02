#include <istream>
#include <ostream>

#include "ip_address.hpp"

namespace dts {

std::ostream &operator<<(std::ostream &os, const IPv4 &ip) {
    for (const auto i : {3uz, 2uz, 1uz}) {
        os << static_cast<std::uint32_t>(ip.parts_[i]) << '.';
    }
    os << static_cast<std::uint32_t>(ip.parts_[0]);
    return os;
}

static std::uint8_t read_part(std::istream &is) {
    std::uint32_t part{};
    is >> part;
    if (part > std::numeric_limits<std::uint8_t>::max()) {
        is.setstate(std::ios_base::failbit);
        return std::numeric_limits<std::uint8_t>::max();
    } else {
        return static_cast<std::uint8_t>(part);
    }
}

std::istream &operator>>(std::istream &is, IPv4 &ip) {
    for (char dot{}; const auto i : {3uz, 2uz, 1uz}) {
        ip.parts_[i] = read_part(is);
        is >> dot;
        if (dot != '.') {
            is.setstate(std::ios_base::failbit);
        }
    }

    ip.parts_[0] = read_part(is);
    return is;
}

} // namespace dts
