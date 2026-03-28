#ifndef INCLUDE_BINARY_TREE_HPP
#define INCLUDE_BINARY_TREE_HPP

#include <deque>
#include <functional>
#include <memory>

namespace dts {

class BinaryTree final {
  public:
    struct Node final {
        explicit Node(int value) : value_{value} {}

        std::shared_ptr<Node> get_left() noexcept { return left_; }
        std::shared_ptr<const Node> get_left() const noexcept { return left_; }

        std::shared_ptr<Node> get_right() noexcept { return right_; }
        std::shared_ptr<const Node> get_right() const noexcept { return right_; }

        std::weak_ptr<Node> get_parent() noexcept { return parent_; }
        std::weak_ptr<const Node> get_parent() const noexcept { return parent_; }

        void set_left(std::shared_ptr<Node> node) noexcept { set<&Node::left_>(std::move(node)); }
        void set_right(std::shared_ptr<Node> node) noexcept { set<&Node::right_>(std::move(node)); }

        int get_value() const noexcept { return value_; }

      private:
        friend BinaryTree;

        template <std::shared_ptr<Node> Node::*MemberPtr>
        void set(std::shared_ptr<Node> node) noexcept {
            node->parent_ = node;
            this->*MemberPtr = std::move(node);
        }

        std::shared_ptr<Node> left_;
        std::shared_ptr<Node> right_;
        std::weak_ptr<Node> parent_;
        int value_;
    };

    std::shared_ptr<Node> root;

    template <typename F>
    void bfs(F &&callback) const {
        std::deque<const Node *> queue;

        queue.push_back(std::addressof(*root));

        while (!queue.empty()) {
            const auto *next = queue.front();
            queue.pop_front();

            std::invoke(callback, next->get_value());

            if (next->left_) {
                queue.push_back(std::addressof(*next->left_));
            }
            if (next->right_) {
                queue.push_back(std::addressof(*next->right_));
            }
        }
    }

    template <typename F>
    void dfs(F &&callback) const {
        do_dfs(std::forward<F>(callback), *root);
    }

  private:
    template <typename F>
    static void do_dfs(F &&callback, const Node &node) {
        std::invoke(callback, node.get_value());

        if (node.left_) {
            do_dfs(callback, *node.left_);
        }

        if (node.right_) {
            do_dfs(callback, *node.right_);
        }
    }
};

} // namespace dts

#endif // INCLUDE_BINARY_TREE_HPP
