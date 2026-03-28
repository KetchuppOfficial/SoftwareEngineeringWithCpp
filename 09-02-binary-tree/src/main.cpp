#include <iostream>

#include "binary_tree.hpp"

int main() {
    /*
     *       1
     *      / \
     *     /   \
     *    2     3
     *   / \   / \
     *  4   5 6   7
     */
    const auto tree = [] {
        dts::BinaryTree tree;

        tree.root = std::make_shared<dts::BinaryTree::Node>(1);

        tree.root->set_left(std::make_shared<dts::BinaryTree::Node>(2));
        tree.root->set_right(std::make_shared<dts::BinaryTree::Node>(3));

        tree.root->get_left()->set_left(std::make_shared<dts::BinaryTree::Node>(4));
        tree.root->get_left()->set_right(std::make_shared<dts::BinaryTree::Node>(5));
        tree.root->get_right()->set_left(std::make_shared<dts::BinaryTree::Node>(6));
        tree.root->get_right()->set_right(std::make_shared<dts::BinaryTree::Node>(7));

        return tree;
    }();

    auto print = [](int val) static { std::cout << val; };

    std::cout << "DFS: ";
    tree.dfs(print);
    std::cout << '\n';

    std::cout << "BFS: ";
    tree.bfs(print);
    std::cout << '\n';
}
