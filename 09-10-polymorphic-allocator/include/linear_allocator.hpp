#ifndef INCLUDE_LINEAR_ALLOCATOR_HPP
#define INCLUDE_LINEAR_ALLOCATOR_HPP

#include <cstddef>
#include <memory>
#include <new>
#include <ostream>

#include "allocator_base.hpp"

namespace dts {

class LinearAllocator final : public Allocator {
  public:
    explicit LinearAllocator(std::size_t size)
        : m_size(size), m_begin{operator new(size, std::align_val_t(kDefaultAlignment))} {}

    LinearAllocator(const LinearAllocator &) = delete;
    LinearAllocator &operator=(const LinearAllocator &) = delete;

    ~LinearAllocator() { operator delete(m_begin, m_size, std::align_val_t(kDefaultAlignment)); }

    void show(std::ostream &os) const {
        std::print(os, "LinearAllocator::show : m_size = {} m_begin = {:018} m_offset = {:0>4}\n",
                   m_size, m_begin, m_offset);
    }

  private:
    void *do_allocate(std::size_t size, std::size_t alignment) override {
        void *begin = Allocator::get<std::byte>(m_begin) + m_offset;

        auto free = m_size - m_offset;

        begin = std::align(alignment, size, begin, free);
        if (!begin) {
            return nullptr;
        }

        m_offset = m_size - free + size;
        return begin;
    }

    void do_deallocate([[maybe_unused]] void *ptr, [[maybe_unused]] std::size_t size,
                       [[maybe_unused]] std::size_t alignment) override { /* noop */ }

    std::size_t m_size = 0;
    std::size_t m_offset = 0;
    void *m_begin = nullptr;
};

} // namespace dts

#endif // INCLUDE_LINEAR_ALLOCATOR_HPP
