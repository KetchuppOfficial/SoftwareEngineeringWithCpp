#ifndef INCLUDE_FACTORY_HPP
#define INCLUDE_FACTORY_HPP

#include <string>
#include <memory>

namespace dts {

class Entity {
  public:
    virtual ~Entity() = default;

    virtual std::string who_am_i() const = 0;
};

class Client final : public Entity {
    std::string who_am_i() const override { return "Client"; }
};

class Server final : public Entity {
    std::string who_am_i() const override { return "Server"; }
};

class Factory {
  public:
    virtual ~Factory() = default;

    virtual std::unique_ptr<Entity> make_entity() const = 0;
};

class FactoryClient : public Factory {
  public:
    std::unique_ptr<Entity> make_entity() const override { return std::make_unique<Client>(); }
};

class FactoryServer : public Factory {
  public:
    std::unique_ptr<Entity> make_entity() const override { return std::make_unique<Server>(); }
};

} // namespace dts

#endif // INCLUDE_FACTORY_HPP
