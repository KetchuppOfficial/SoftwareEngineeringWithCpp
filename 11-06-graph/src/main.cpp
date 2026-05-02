#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <print>
#include <random>
#include <ranges>
#include <vector>

#include <boost/graph/adjacency_matrix.hpp>

namespace {

using EdgeWeight = int;
using Graph = boost::adjacency_matrix<boost::undirectedS, /*VertexProperty=*/boost::no_property,
                                      /*EdgeProperty=*/EdgeWeight>;

Graph create_complete_graph(std::size_t n_vertices) {

    std::ranges::view auto kVertices = std::views::iota(0uz, n_vertices);

    std::default_random_engine engine{std::random_device{}()};
    std::uniform_int_distribution<EdgeWeight> edge_weight(1, static_cast<int>(n_vertices));

    Graph graph(n_vertices);
    for (const auto i : kVertices) {
        for (const auto j : kVertices | std::views::drop(i + 1)) {
            boost::add_edge(i, j, edge_weight(engine), graph);
        }
    }

    return graph;
}

EdgeWeight path_weight(const Graph &graph, const std::vector<std::size_t> &vertices) {
    const auto &last_edge = graph.get_edge(vertices.back(), vertices.front());
    assert(last_edge.first);

    std::ranges::view auto weights =
        vertices | std::views::adjacent<2> | std::views::transform([&graph](auto tup) {
            const auto &[from, to] = tup;
            const auto &edge = graph.get_edge(from, to);
            assert(edge.first);
            return edge.second;
        });

    return std::ranges::fold_left(weights, last_edge.second, std::plus{});
}

std::pair<std::vector<std::size_t>, EdgeWeight> compute_optimal_path(const Graph &graph) {
    std::vector path(std::from_range, std::views::iota(0uz, graph.m_vertex_set.size()));

    std::vector<std::size_t> optimal_path(path.size());
    auto min_path_weight = std::numeric_limits<EdgeWeight>::max();
    do {
        const auto weight = path_weight(graph, path);
        if (weight < min_path_weight) {
            min_path_weight = weight;
            optimal_path.assign_range(path);
        }
    } while (std::next_permutation(path.begin(), path.end()));

    return {std::move(optimal_path), min_path_weight};
}

void print_graph(std::ostream &os, const Graph &graph) {
    const auto size = graph.m_vertex_set.size();
    std::ranges::view auto indices = std::views::iota(0uz, size);

    os << "    0";
    for (const auto i : indices | std::views::drop(1)) {
        std::print(os, " {:2}", i);
    }
    os << '\n';

    for (const auto i : indices) {
        std::print(os, "{:2}", i);
        for (const auto j : indices) {
            const auto &[exists, value] = graph.get_edge(i, j);
            if (exists) {
                std::print(os, " {:2}", value);
            } else {
                os << "  _";
            }
        }
        os << '\n';
    }
}

} // unnamed namespace

int main() try {
    constexpr std::size_t kVerticesCount = 10;
    const auto graph = create_complete_graph(kVerticesCount);

    const auto [path, path_weight] = compute_optimal_path(graph);

    std::println(std::cout, "optimal path: {} -> {}",
                 std::views::join_with(path | std::views::transform([](EdgeWeight e) static {
                                           return std::to_string(e);
                                       }),
                                       " -> ") |
                     std::ranges::to<std::string>(),
                 path.front());
    std::println(std::cout, "cost: {}", path_weight);

    std::cout << "matrix:\n";
    print_graph(std::cout, graph);
} catch (const std::exception &e) {
    std::println(stderr, "Caught an instance of {}.\nwhat(): {}", typeid(e).name(), e.what());
    return EXIT_FAILURE;
} catch (...) {
    std::println(stderr, "Caught an unknown exception.");
    return EXIT_FAILURE;
}
