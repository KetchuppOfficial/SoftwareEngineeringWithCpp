#ifndef INCLUDE_FREE_LIST_ALLOCATOR_HPP
#define INCLUDE_FREE_LIST_ALLOCATOR_HPP

#include <cstddef>
#include <format>
#include <memory>
#include <new>
#include <ostream>
#include <stdexcept>

#include "allocator_base.hpp"

namespace dts {

class FreeListAllocator : public Allocator {
  public:
    explicit FreeListAllocator(std::size_t size) : m_size(size) {
        if (size < sizeof(Node) + 1) {
            throw std::invalid_argument{std::format(
                "cannot create FreeListAllocator with size less than {}", sizeof(Node) + 1)};
        }

        m_begin = operator new(m_size, std::align_val_t(kDefaultAlignment));
        m_head = get<Node>(m_begin);
        m_head->size = m_size - sizeof(Header);
        m_head->next = nullptr;
    }

    FreeListAllocator(const FreeListAllocator &) = delete;
    FreeListAllocator &operator=(const FreeListAllocator &) = delete;

    ~FreeListAllocator() { operator delete(m_begin, m_size, std::align_val_t(kDefaultAlignment)); }

    void show(std::ostream &os) const {
        std::print(os, "FreeListAllocator::show : m_size = {} m_begin = {:018} m_head = {:018} ",
                   m_size, m_begin, static_cast<void *>(m_head));
        if (m_head->next) {
            std::println(os, "m_head->next = {:018}", static_cast<void *>(m_head->next));
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

    void *do_allocate(std::size_t size, [[maybe_unused]] std::size_t alignment) override {
        void *end = get<std::byte>(m_begin) + sizeof(Header) + size, *next = end;

        auto free = 2 * alignof(Header);

        if (next = std::align(alignof(Header), sizeof(Header), next, free); next) {
            auto padding = get<std::byte>(next) - get<std::byte>(end);

            if (auto [current, previous] = find(size + padding); current) {
                if (current->size >= size + padding + sizeof(Node) + 1) {
                    auto step = sizeof(Header) + size + padding;

                    auto node = get<Node>(get<std::byte>(current) + step);

                    node->size = current->size - step;

                    node->next = current->next;

                    current->next = node;
                } else {
                    padding += current->size - size - padding;
                }

                if (!previous) {
                    m_head = current->next;
                } else {
                    previous->next = current->next;
                }

                auto header = get<Header>(current);

                header->size = size + padding;

                return get<std::byte>(current) + sizeof(Header);
            }
        }

        return nullptr;
    }

    void do_deallocate(void *ptr, [[maybe_unused]] std::size_t size,
                       [[maybe_unused]] std::size_t alignment) override {
        auto node = get<Node>(get<std::byte>(ptr) - sizeof(Header));

        Node *previous = nullptr, *current = m_head;

        while (current) {
            if (node < current) {
                node->next = current;

                if (!previous) {
                    m_head = node;
                } else {
                    previous->next = node;
                }

                break;
            }

            previous = current;

            current = current->next;
        }

        merge(previous, node);
    }

    auto find(std::size_t size) const -> std::pair<Node *, Node *> {
        Node *current = m_head, *previous = nullptr;

        while (current && size > current->size) {
            previous = current;

            current = current->next;
        }

        return std::make_pair(current, previous);
    }

    void merge(Node *previous, Node *node) const {
        if (node->next &&
            get<std::byte>(node) + sizeof(Header) + node->size == get<std::byte>(node->next)) {
            node->size += sizeof(Header) + node->next->size;

            node->next = node->next->next;
        }

        if (previous &&
            get<std::byte>(previous) + sizeof(Header) + previous->size == get<std::byte>(node)) {
            previous->size += sizeof(Header) + node->size;

            previous->next = node->next;
        }
    }

    std::size_t m_size = 0;
    void *m_begin = nullptr;
    Node *m_head = nullptr;
};

} // namespace dts

#endif // INCLUDE_FREE_LIST_ALLOCATOR_HPP
