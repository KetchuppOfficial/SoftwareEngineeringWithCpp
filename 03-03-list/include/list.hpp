#ifndef INCLUDE_LIST_HPP
#define INCLUDE_LIST_HPP

#include <cassert>
#include <iosfwd>
#include <optional>
#include <utility>

namespace dts {

class List final {
  public:
    List() = default;

    List(const List &) = delete;
    List &operator=(const List &) = delete;

    List(List &&) = delete;
    List &operator=(List &&) = delete;

    ~List() {
        if (empty()) {
            return;
        }

        for (auto *node = head_; node != tail_;) {
            auto next = node->next;
            delete node;
            node = next;
        }
        delete tail_;
    }

    bool empty() const noexcept { return head_ == nullptr; }

    void show(std::ostream &os) const;

    void push_front(int value) {
        if (empty()) {
            head_ = tail_ = new Node{nullptr, value};
        } else {
            head_ = new Node{head_, value};
        }
    }

    void push_back(int value) {
        auto *node = new Node{nullptr, value};
        if (empty()) {
            head_ = tail_ = node;
        } else {
            assert(tail_);
            tail_->next = node;
            tail_ = node;
        }
    }

    void pop_front() {
        assert(!empty());

        if (auto *new_head = head_->next) {
            delete head_;
            head_ = new_head;
        } else {
            delete head_;
            head_ = nullptr;
            tail_ = nullptr;
        }
    }

    // Oops: O(n)
    void pop_back() {
        assert(!empty());

        if (auto *next = head_->next) {
            auto *node = head_;
            while (next) {
                node = std::exchange(next, next->next);
            }
            assert(node);
            node->next = nullptr;
            delete tail_;
            tail_ = node;
        } else {
            delete tail_;
            head_ = nullptr;
            tail_ = nullptr;
        }
    }

    std::optional<int> get() const {
        if (empty()) {
            return std::nullopt;
        }

        auto node = head_;
        auto mean = head_;
        for (;;) {
            node = node->next;
            if (!node) {
                break;
            }

            node = node->next;
            if (!node) {
                break;
            }

            mean = mean->next;
        }

        return mean->value;
    }

  private:
    struct Node {
        Node *next;
        int value;
    };

    Node *head_ = nullptr;
    Node *tail_ = nullptr;
};

} // namespace dts

#endif // INCLUDE_LIST_HPP
