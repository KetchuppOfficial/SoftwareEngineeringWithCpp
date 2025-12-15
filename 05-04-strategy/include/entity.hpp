#ifndef INCLUDE_ENTITY_HPP
#define INCLUDE_ENTITY_HPP

#include <string>

namespace dts {

template <typename T>
class Entity : private T {
  public:
    explicit Entity(int n) : number_{n} {}

    std::string convert() const { return T::convert(number_); }

  private:
    int number_;
};

} // namespace dts

#endif // INCLUDE_ENTITY_HPP
