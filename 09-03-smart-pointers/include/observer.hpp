#ifndef INCLUDE_OBSERVER_HPP
#define INCLUDE_OBSERVER_HPP

#include <memory>
#include <print>
#include <utility>
#include <vector>

namespace dts {

class Observer {
  public:
    explicit Observer(std::ostream &os) : os_{os} {}

    virtual ~Observer() = default;

    virtual void test(int x) const = 0;

  protected:
    std::ostream &os_;
};

class Entity {
  public:
    void add(std::unique_ptr<Observer> observer) { m_observers.push_back(std::move(observer)); }

    void set(int x) {
        m_x = x;
        notify_all();
    }

    void notify_all() const {
        for (const auto &observer : m_observers) {
            if (observer) {
                observer->test(m_x);
            }
        }
    }

  private:
    int m_x = 0;

    std::vector<std::unique_ptr<Observer>> m_observers;
};

class Client : public Observer {
  public:
    using Observer::Observer;

    void test(int x) const override { return std::println(os_, "Client::test : x = {}", x); }
};

class Server : public Observer {
  public:
    using Observer::Observer;

    void test(int x) const override { return std::println(os_, "Server::test : x = {}", x); }
};

} // namespace dts

#endif // INCLUDE_OBSERVER_HPP
