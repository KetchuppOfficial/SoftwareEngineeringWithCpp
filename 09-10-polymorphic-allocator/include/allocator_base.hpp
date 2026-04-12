#ifndef INCLUDE_ALLOCATOR_BASE_HPP
#define INCLUDE_ALLOCATOR_BASE_HPP

#include <cstddef>

namespace dts {

class Allocator {
  public:
    static constexpr std::size_t kDefaultAlignment = alignof(std::max_align_t);

    virtual ~Allocator() = default;

    void *allocate(std::size_t size, std::size_t alignment = kDefaultAlignment) {
        return do_allocate(size, alignment);
    }

    void deallocate(void *ptr, std::size_t size, std::size_t alignment = kDefaultAlignment) {
        do_deallocate(ptr, size, alignment);
    }

  protected:
    template <typename T>
    static T *get(void *x) {
        return static_cast<T *>(x);
    }

  private:
    virtual void *do_allocate(std::size_t size, std::size_t alignment) = 0;
    virtual void do_deallocate(void *ptr, std::size_t size, std::size_t alignment) = 0;
};

} // namespace dts

#endif // INCLUDE_ALLOCATOR_BASE_HPP
