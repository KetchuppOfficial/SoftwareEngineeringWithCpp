#include <cassert>
#include <iostream>
#include <vector>

#include <benchmark/benchmark.h>

#include "stack_allocator.hpp"

void test_v1(benchmark::State &state) {
    auto kb = 1uz << 10, mb = 1uz << 20;

    std::vector<void *> vector(kb, nullptr);

    for (auto element : state) {
        for (auto i = 0uz; i < kb; ++i) {
            vector[i] = operator new(mb);
        }

        for (auto i = 0uz; i < kb; ++i) {
            operator delete(vector[vector.size() - 1 - i], mb);
        }

        benchmark::DoNotOptimize(vector);
    }
}

void test_v2(benchmark::State &state) {
    auto kb = 1uz << 10, mb = 1uz << 20, gb = 1uz << 30;

    std::vector<void *> vector(kb, nullptr);

    for (auto element : state) {
        const std::unique_ptr<dts::Allocator> allocator =
            std::make_unique<dts::StackAllocator>(2 * gb);

        for (auto i = 0uz; i < kb; ++i) {
            vector[i] = allocator->allocate(mb);
        }

        for (auto i = 0uz; i < kb; ++i) {
            allocator->deallocate(vector[std::size(vector) - 1 - i], mb);
        }

        benchmark::DoNotOptimize(vector);
    }
}

BENCHMARK(test_v1);

BENCHMARK(test_v2);

int main() {
    dts::StackAllocator allocator(1 << 10);

    allocator.show(std::cout);
    allocator.allocate(1, 1);

    allocator.show(std::cout);
    allocator.allocate(2, 2);

    allocator.show(std::cout);
    auto x = allocator.allocate(4, 4);

    allocator.show(std::cout);
    auto y = allocator.allocate(8, 8);

    allocator.show(std::cout);
    allocator.deallocate(y, 8);

    allocator.show(std::cout);
    allocator.deallocate(x, 4);

    allocator.show(std::cout);
    auto z = allocator.allocate(8, 8);

    allocator.show(std::cout);

    assert(z == x);

    benchmark::RunSpecifiedBenchmarks();
}
