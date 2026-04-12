#ifndef INCLUDE_STACK_ALLOCATOR_HPP
#define INCLUDE_STACK_ALLOCATOR_HPP

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <new>

#include "allocator_base.hpp"

namespace dts {

class StackAllocator final : public Allocator {
    using Header = std::uint8_t;

  public:
    explicit StackAllocator(std::size_t size) : m_size(size) {
        m_begin = operator new(m_size, std::align_val_t(kDefaultAlignment));
    }

    StackAllocator(const StackAllocator &) = delete;
    StackAllocator &operator=(const StackAllocator &) = delete;

    ~StackAllocator() { operator delete(m_begin, m_size, std::align_val_t(kDefaultAlignment)); }

    void show(std::ostream &os) const {
        std::print(os, "StackAllocator::show : m_size = {} m_begin = {:018} m_offset = {:0>4}\n",
                   m_size, m_begin, m_offset);
    }

  private:
    void *do_allocate(std::size_t size, std::size_t alignment) override {
        void *begin = get<std::byte>(m_begin) + m_offset + sizeof(Header);

        auto free = m_size - m_offset - sizeof(Header);

        begin = std::align(alignment, size, begin, free);
        if (!begin) {
            return nullptr;
        }

        auto header = get<Header>(get<std::byte>(begin) - sizeof(Header));
        *header = std::distance(get<std::byte>(m_begin) + m_offset, get<std::byte>(begin));
        m_offset = get<std::byte>(begin) - get<std::byte>(m_begin) + size;
        return begin;
    }

    void do_deallocate(void *ptr, [[maybe_unused]] std::size_t size,
                       [[maybe_unused]] std::size_t alignment) override {
        auto header = get<Header>(get<std::byte>(ptr) - sizeof(Header));
        m_offset = get<std::byte>(ptr) - get<std::byte>(m_begin) - *header;
    }

    std::size_t m_size = 0;
    std::size_t m_offset = 0;
    void *m_begin = nullptr;
};

} // namespace dts

#endif // INCLUDE_STACK_ALLOCATOR_HPP
