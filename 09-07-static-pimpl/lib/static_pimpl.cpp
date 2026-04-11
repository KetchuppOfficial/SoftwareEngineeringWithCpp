#include <format>
#include <memory>
#include <new>
#include <utility>

#include "static_pimpl.hpp"

namespace dts {

class Entity::Implementation {
  public:
    std::string test() const { return std::format("{}", value_); }

  private:
    int value_ = 42;
};

Entity::Entity() {
    static_assert(alignof(Entity::Implementation) <= alignof(std::max_align_t));
    static_assert(sizeof(Entity::Implementation) <= kMaxStorageSize);

    new (m_storage.data()) Implementation{};
    fill_rest();
}

Entity::Entity(Entity &&other) {
    new (m_storage.data()) Implementation(std::move(*other.get()));
    fill_rest();
}

Entity::~Entity() { std::destroy_at(get()); }

Entity &Entity::operator=(Entity &&other) {
    std::destroy_at(get());
    new (m_storage.data()) Implementation(std::move(*other.get()));
    return *this;
}

std::string Entity::test() const { return get()->test(); }

auto Entity::get() noexcept -> Implementation * {
    return std::launder(reinterpret_cast<Implementation *>(m_storage.data()));
}

auto Entity::get() const noexcept -> const Implementation * {
    return std::launder(reinterpret_cast<const Implementation *>(m_storage.data()));
}

void Entity::fill_rest() {
    std::fill(m_storage.begin() + sizeof(Implementation), m_storage.end(),
              std::byte{}); // just for the peace of mind
}

} // namespace dts
