#ifndef INCLUDE_LIST_ALLOCATOR_HPP
#define INCLUDE_LIST_ALLOCATOR_HPP

#include <cstddef>
#include <format>
#include <new>
#include <ostream>
#include <stdexcept>
#include <vector>

#include "allocator_base.hpp"

namespace dts {

class ListAllocator final : public Allocator {
  public:
    ListAllocator(std::size_t size, std::size_t step) : m_size(size), m_step(step) {
        if (size % step != 0) {
            throw std::invalid_argument{"size is not dividable by step"};
        } else if (step < sizeof(Node)) {
            throw std::invalid_argument{std::format(
                "given step of {} is less than the minimal value of {}", step, sizeof(Node))};
        }

        make_list();
        m_begin = m_head;
    }

    ListAllocator(const ListAllocator &) = delete;
    ListAllocator &operator=(const ListAllocator &) = delete;

    ~ListAllocator() {
        for (auto list : m_lists) {
            operator delete(list, m_size, std::align_val_t(kDefaultAlignment));
        }
    }

    void show(std::ostream &os) const {
        std::println(
            os,
            "ListAllocator::show : m_size = {} m_step = {} m_begin = {:018} m_head = {:018} "
            "m_offset = {}",
            m_size, m_step, m_begin, static_cast<void *>(m_head), m_offset);
    }

  private:
    struct Node {
        Node *next = nullptr;
    };

    void *do_allocate([[maybe_unused]] std::size_t size,
                      [[maybe_unused]] std::size_t alignment) override {
        if (!m_head) {
            if (m_offset == m_lists.size()) {
                make_list();
            } else {
                m_head = get<Node>(m_lists[++m_offset - 1]);
            }
        }

        auto node = m_head;

        if (node->next) {
            m_head = m_head->next;
        } else {
            auto next = get<std::byte>(node) + m_step;
            if (next != get<std::byte>(m_lists[m_offset - 1]) + m_size) {
                m_head = get<Node>(next);
                m_head->next = nullptr;
            } else {
                m_head = m_head->next;
            }
        }

        return node;
    }

    void do_deallocate(void *ptr, [[maybe_unused]] std::size_t size,
                       [[maybe_unused]] std::size_t alignment) override {
        auto node = get<Node>(ptr);
        node->next = m_head;
        m_head = node;
    }

    void make_list() {
        m_head = get<Node>(operator new(m_size, std::align_val_t(kDefaultAlignment)));
        m_head->next = nullptr;
        ++m_offset;
        m_lists.push_back(m_head);
    }

    std::size_t m_size = 0;
    std::size_t m_step = 0;
    std::size_t m_offset = 0;
    void *m_begin = nullptr;
    Node *m_head = nullptr;
    std::vector<void *> m_lists;
};

} // namespace dts

#endif // INCLUDE_LIST_ALLOCATOR_HPP
