#ifndef BIDIRECTIONAL_LIST_HPP
#define BIDIRECTIONAL_LIST_HPP

#include <cassert>
#include <iterator>
#include <memory>
#include <utility>

namespace dts {

template <typename T>
class List {
  private:
    struct NodeBase {
        std::shared_ptr<NodeBase> next;
        std::weak_ptr<NodeBase> prev;
    };

    struct Node : public NodeBase {
        explicit Node(T val) : value(std::move(val)) {}
        explicit Node(T val, std::shared_ptr<NodeBase> next, std::weak_ptr<NodeBase> prev)
            : NodeBase(std::move(next), std::move(prev)), value(std::move(val)) {}

        T value;
    };

  public:
    class Iterator final {
      public:
        using value_type = const T;
        using pointer = value_type *;
        using reference = value_type &;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        Iterator() = default;
        Iterator(std::shared_ptr<NodeBase> node) : m_node(std::move(node)) {}

        reference operator*() const { return std::static_pointer_cast<const Node>(m_node)->value; }
        pointer operator->() const { return std::addressof(**this); }

        Iterator &operator++() {
            m_node = m_node->next;
            return *this;
        }

        Iterator operator++(int) {
            auto curr = *this;
            ++(*this);
            return curr;
        }

        Iterator &operator--() {
            m_node = m_node->prev.lock();
            return *this;
        }

        Iterator operator--(int) {
            auto curr = *this;
            --(*this);
            return *this;
        }

        bool operator==(const Iterator &rhs) const = default;

      private:
        std::shared_ptr<NodeBase> m_node;
    };

    static_assert(std::bidirectional_iterator<Iterator>);

    List() : m_sentinel{std::make_shared<NodeBase>()} {}

    using const_iterator = Iterator;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    const_iterator begin() const { return {m_sentinel->next}; }
    const_iterator end() const { return {m_sentinel}; }
    const_reverse_iterator rbegin() const { return std::reverse_iterator{end()}; }
    const_reverse_iterator rend() const { return std::reverse_iterator{begin()}; }

    void push_back(T value) {
        auto &head = get_head();
        auto &tail = get_tail();
        if (head) {
            assert(!tail.expired());
            auto node = std::make_shared<Node>(std::move(value), m_sentinel, tail);
            auto tail_shared = tail.lock();
            tail = node;
            tail_shared->next = std::move(node);
        } else {
            tail = head = std::make_shared<Node>(std::move(value), m_sentinel, m_sentinel);
        }
    }

  private:
    std::shared_ptr<NodeBase> &get_head() { return m_sentinel->next; }
    const std::shared_ptr<NodeBase> &get_head() const { return m_sentinel->next; }

    std::weak_ptr<NodeBase> &get_tail() { return m_sentinel->prev; }
    const std::weak_ptr<NodeBase> &get_tail() const { return m_sentinel->prev; }

    std::shared_ptr<NodeBase> m_sentinel;
};

} // namespace dts

#endif // BIDIRECTIONAL_LIST_HPP
