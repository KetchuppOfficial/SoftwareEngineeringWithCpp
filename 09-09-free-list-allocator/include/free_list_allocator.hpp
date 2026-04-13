#ifndef INCLUDE_FREE_LIST_ALLOCATOR_HPP
#define INCLUDE_FREE_LIST_ALLOCATOR_HPP

#include <cstddef>
#include <format>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

namespace dts {

/*
 * Single entry structure:
 * | Header | Space given to the user | Padding |
 */
class FreeListAllocator final {
  public:
    enum class SearchPolicy : bool { first, best };

    explicit FreeListAllocator(std::size_t size, SearchPolicy search_policy)
        : m_size(size), m_search_policy{search_policy} {
        if (m_size < sizeof(Node) + 1) {
            throw std::invalid_argument{
                std::format("trying to create allocator for {} bytes, but the minimal size is {}",
                            m_size, sizeof(Node) + 1)};
        }

        m_begin = operator new(m_size, std::align_val_t(kAlignment));

        m_head = get_node(m_begin);
        m_head->size = m_size - sizeof(Header);
        m_head->next = nullptr;
    }

    FreeListAllocator(const FreeListAllocator &) = delete;
    FreeListAllocator &operator=(const FreeListAllocator &) = delete;

    ~FreeListAllocator() { operator delete(m_begin, m_size, std::align_val_t(kAlignment)); }

    auto allocate(std::size_t size) -> void * {
        void *end = get_byte(m_begin) + sizeof(Header) + size, *next = end;

        auto free = 2 * alignof(Header);

        next = std::align(alignof(Header), sizeof(Header), next, free);
        if (!next) {
            return nullptr;
        }

        auto padding = get_byte(next) - get_byte(end);

        auto [current, previous] = find(size + padding);
        if (!current) {
            return nullptr;
        }

        if (current->size < size + padding + sizeof(Node) + 1) {
            padding += current->size - size - padding;
        } else {
            auto step = sizeof(Header) + size + padding;
            auto node = get_node(get_byte(current) + step);
            node->size = current->size - step;
            node->next = current->next;
            current->next = node;
        }

        if (previous) {
            previous->next = current->next;
        } else {
            m_head = current->next;
        }

        auto header = get_header(current);
        header->size = size + padding;

        return get_byte(current) + sizeof(Header);
    }

    void deallocate(void *x) {
        auto node = get_node(get_byte(x) - sizeof(Header));

        Node *previous = nullptr, *current = m_head;

        while (current) {
            if (node < current) {
                node->next = current;

                if (previous) {
                    previous->next = node;
                } else {
                    m_head = node;
                }

                break;
            }

            previous = std::exchange(current, current->next);
        }

        merge(previous, node);
    }

    //  -------------------------------------------------------------------------------------------

    void show(std::ostream &os) const {
        std::print(os, "Chain_Allocator::show : m_size = {} m_begin = {:018} m_head = {:018} ",
                   m_size, m_begin, static_cast<void *>(m_head));

        if (m_head->next) {
            std::print(os, "m_head->next = {:018}\n", static_cast<void *>(m_head->next));
        } else {
            os << '\n';
        }
    }

  private:
    struct Node {
        std::size_t size = 0;
        Node *next = nullptr;
    };

    struct alignas(std::max_align_t) Header {
        std::size_t size = 0;
    };

    static std::byte *get_byte(void *x) { return static_cast<std::byte *>(x); }
    static Node *get_node(void *x) { return static_cast<Node *>(x); }
    static Header *get_header(void *x) { return static_cast<Header *>(x); }

    std::pair<Node *, Node *> find(std::size_t size) const {
        switch (m_search_policy) {
            case SearchPolicy::first:
                return find_first(size);
            case SearchPolicy::best:
                return find_best(size);
            default:
                std::unreachable();
        }
    }

    std::pair<Node *, Node *> find_first(std::size_t size) const {
        Node *current = m_head, *previous = nullptr;

        while (current && size > current->size) {
            previous = std::exchange(current, current->next);
        }

        return std::pair{current, previous};
    }

    std::pair<Node *, Node *> find_best(std::size_t size) const {
        Node *current = m_head;
        Node *previous = nullptr;

        Node *best = current;
        Node *before_best = nullptr;
        std::size_t min_size = best->size;

        while (current) {
            if (current->size >= size) {
                if (current->size < min_size) {
                    min_size = current->size;
                    best = current;
                    before_best = previous;
                }
            }
            previous = std::exchange(current, current->next);
        }

        return std::pair{best, before_best};
    }

    void merge(Node *previous, Node *node) const {
        if (node->next && get_byte(node) + sizeof(Header) + node->size == get_byte(node->next)) {
            node->size += sizeof(Header) + node->next->size;
            node->next = node->next->next;
        }

        if (previous && get_byte(previous) + sizeof(Header) + previous->size == get_byte(node)) {
            previous->size += sizeof(Header) + node->size;
            previous->next = node->next;
        }
    }

    std::size_t m_size = 0;
    SearchPolicy m_search_policy;
    void *m_begin = nullptr;
    Node *m_head = nullptr;

    static constexpr std::size_t kAlignment = alignof(std::max_align_t);
};

} // namespace dts

#endif // INCLUDE_FREE_LIST_ALLOCATOR_HPP
