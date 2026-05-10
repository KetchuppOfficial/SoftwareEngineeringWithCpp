#ifndef INCLUDE_CURRENCY_EXCHANGER_HPP
#define INCLUDE_CURRENCY_EXCHANGER_HPP

#include <iomanip>
#include <ios>
#include <istream>
#include <ostream>

namespace dts {

inline void convert_rubles_to_dollars(std::istream &is, std::ostream &os,
                                      long double exchange_rate) {
    long double value{};
    is >> std::get_money(value);
    if (is.bad() || is.fail()) {
        throw std::runtime_error{"could not parse input monetary value"};
    }
    os << std::showbase << std::put_money(value / exchange_rate);
}

} // namespace dts

#endif // INCLUDE_CURRENCY_EXCHANGER_HPP
