#ifndef INCLUDE_CLIENT_HPP
#define INCLUDE_CLIENT_HPP

#include "entity_v1.hpp"
#include "entity_v2.hpp"

namespace dts {

class Adapter_v1 : public Entity_v1 {
  public:
    ~Adapter_v1() override = default;

    virtual int test_v1() const = 0;
    int test() const override { return test_v1(); }
};

class Adapter_v2 : public Entity_v2 {
  public:
    ~Adapter_v2() override = default;

    virtual int test_v2() const = 0;
    int test() const override { return test_v2(); }
};

class Client final : public Adapter_v1, public Adapter_v2 {
  public:
    ~Client() override = default;

    int test_v1() const override { return 42; }
    int test_v2() const override { return 43; }
};

} // namespace dts

#endif // INCLUDE_CLIENT_HPP