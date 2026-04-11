#ifndef INCLUDE_STATIC_PIMPL_HPP
#define INCLUDE_STATIC_PIMPL_HPP

#include <array>
#include <cstddef>
#include <string>

namespace dts {

class Entity final {
  public:
    Entity();

    Entity(Entity &&other);
    Entity &operator=(Entity &&other);

    ~Entity();

    std::string test() const;

  private:
    class Implementation;

    Implementation *get() noexcept;
    const Implementation *get() const noexcept;

    void fill_rest();

    static constexpr std::size_t kMaxStorageSize = 16;

    alignas(std::max_align_t) std::array<std::byte, kMaxStorageSize> m_storage;
};

} // namespace dts

#endif // INCLUDE_STATIC_PIMPL_HPP
