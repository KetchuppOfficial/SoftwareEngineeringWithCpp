#ifndef INCLUDE_EXCEPTION_HPP
#define INCLUDE_EXCEPTION_HPP

#include <exception>

namespace dts {

class Exception : public std::exception {
    const char *what() const noexcept override { return "denominator shall not be zero"; }
};

} // namespace dts

#endif // INCLUDE_EXCEPTION_HPP
