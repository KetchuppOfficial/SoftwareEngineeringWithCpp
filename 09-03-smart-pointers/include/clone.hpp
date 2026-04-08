#ifndef INCLUDE_CLONE_HPP
#define INCLUDE_CLONE_HPP

#include <memory>

namespace dts {

class Entity {
  public:
    explicit Entity(int val) : value_{val} {}

    virtual ~Entity() = default;

    virtual std::unique_ptr<Entity> clone() const = 0;

    int get_value() const noexcept { return value_; }

  private:
    int value_;
};

class Client final : public Entity {
  public:
    Client() : Entity(42) {}

    std::unique_ptr<Entity> clone() const override { return std::make_unique<Client>(*this); }
};

class Server final : public Entity {
  public:
    Server() : Entity(43) {}

    std::unique_ptr<Entity> clone() const override { return std::make_unique<Server>(*this); }
};

} // namespace dts

#endif // INCLUDE_CLONE_HPP