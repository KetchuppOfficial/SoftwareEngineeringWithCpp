#ifndef INCLUDE_COMPOSITE_HPP
#define INCLUDE_COMPOSITE_HPP

#include <algorithm>
#include <cstddef>
#include <functional>
#include <memory>
#include <ranges>
#include <utility>
#include <vector>

namespace dts {

class Entity {
  public:
    virtual ~Entity() = default;

    virtual int test() const = 0;
};

class Client final : public Entity {
  public:
    int test() const override { return 1; }
};

class Server final : public Entity {
  public:
    int test() const override { return 2; }
};

class Composite : public Entity {
  public:
    void add(std::unique_ptr<Entity> entity) { m_entities.push_back(std::move(entity)); }

    int test() const override {
        std::ranges::view auto tested =
            m_entities |
            std::views::filter([](const auto &ptr) static { return static_cast<bool>(ptr); }) |
            std::views::transform([](const auto &entity_ptr) static { return entity_ptr->test(); });

        return std::ranges::fold_left(tested, 0, std::plus<>{});
    }

  private:
    std::vector<std::unique_ptr<Entity>> m_entities;
};

inline std::unique_ptr<Entity> make_composite(std::size_t size_clients, std::size_t size_servers) {
    auto composite = std::make_unique<Composite>();

    for (auto _ : std::views::iota(0uz, size_clients)) {
        composite->add(std::make_unique<Client>());
    }

    for (auto _ : std::views::iota(0uz, size_servers)) {
        composite->add(std::make_unique<Server>());
    }

    return composite;
}

} // namespace dts

#endif // INCLUDE_COMPOSITE_HPP
