#ifndef INCLUDE_DECORATOR_HPP
#define INCLUDE_DECORATOR_HPP

#include <format>
#include <string>
#include <type_traits>

namespace dts {

class Entity {
  public:
    virtual ~Entity() = default;

    virtual std::string test() const = 0;
};

class Placeholder : virtual public Entity {
  public:
    ~Placeholder() override = default;

    std::string test() const override { return "lorem ipsum"; }
};

class BackToTheFuture : virtual public Entity {
  public:
    ~BackToTheFuture() override = default;

    std::string test() const override { return "21.10.2015"; }
};

template <typename T>
class Decorator : virtual public Entity, private T {
  public:
    static_assert(std::is_base_of_v<Entity, T>);

    ~Decorator() override = default;

    std::string test() const override { return std::format("\"{}\"", T::test()); }
};

} // namespace dts

#endif // INCLUDE_DECORATOR_HPP
