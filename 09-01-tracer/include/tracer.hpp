#ifndef INCLUDE_TRACER_HPP
#define INCLUDE_TRACER_HPP

#include <iostream>
#include <source_location>

namespace dts {

class Tracer final {
  public:
    explicit Tracer(std::source_location loc = std::source_location::current()) {
        std::println(std::cout, "Entering '{}' {{ file: {}:{}:{} }}", loc.function_name(),
                     loc.file_name(), loc.line(), loc.column());
    }

    Tracer(const Tracer &) = delete;
    Tracer &operator=(const Tracer &) = delete;

    Tracer(Tracer &&) = delete;
    Tracer &operator=(Tracer &&) = delete;

    ~Tracer() { std::println(std::cout, "Exiting"); }
};

} // namespace dts

#ifdef NDEBUG
#define trace() ;
#else
#define trace()                                                                                    \
    dts::Tracer _ {}
#endif

#endif // INCLUDE_TRACER_HPP
