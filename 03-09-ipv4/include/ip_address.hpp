#ifndef INCLUDE_IP_ADDRESS_HPP
#define INCLUDE_IP_ADDRESS_HPP

#include <compare>
#include <cstdint>
#include <iosfwd>
#include <new>
#include <type_traits>

namespace dts {

class IPv4 final {
  public:
    static_assert(std::is_same_v<std::uint8_t, unsigned char>);

    explicit IPv4() : parts_{} {}
    explicit IPv4(std::uint32_t address) { new (parts_) std::uint32_t{address}; }
    explicit IPv4(std::uint8_t fourth, std::uint8_t third, std::uint8_t second, std::uint8_t first)
        : parts_{first, second, third, fourth} {}

    IPv4 &operator++() {
        auto address = *reinterpret_cast<std::uint32_t *>(parts_);
        ++address;
        new (parts_) std::uint32_t{address};
        return *this;
    }

    IPv4 operator++(int) {
        auto old = *this;
        ++(*this);
        return old;
    }

    IPv4 &operator--() {
        auto address = *reinterpret_cast<std::uint32_t *>(parts_);
        --address;
        new (parts_) std::uint32_t{address};
        return *this;
    }

    IPv4 operator--(int) {
        auto old = *this;
        --(*this);
        return old;
    }

    friend std::strong_ordering operator<=>(const IPv4 &, const IPv4 &) = default;

    friend std::ostream &operator<<(std::ostream &os, const IPv4 &ip);
    friend std::istream &operator>>(std::istream &is, IPv4 &ip);

  private:
    alignas(std::uint32_t) std::uint8_t parts_[4];
};

} // namespace dts

#endif // INCLUDE_IP_ADDRESS_HPP
