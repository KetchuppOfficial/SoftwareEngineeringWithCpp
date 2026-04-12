#include <iostream>
#include <memory>
#include <vector>

#include <benchmark/benchmark.h>

#include "linear_allocator.hpp"

void test_v1(benchmark::State &state) {
    auto kb = 1uz << 10, mb = 1uz << 20;

    std::vector<void *> vector(kb, nullptr);

    for (auto element : state) {
        for (auto i = 0uz; i < kb; ++i) {
            vector[i] = operator new(mb);
        }

        for (auto i = 0uz; i < kb; ++i) {
            operator delete(vector[i], mb);
        }

        benchmark::DoNotOptimize(vector);
    }
}

void test_v2(benchmark::State &state) {
    auto kb = 1uz << 10, mb = 1uz << 20, gb = 1uz << 30;

    std::vector<void *> vector(kb, nullptr);

    for (auto element : state) {
        const std::unique_ptr<dts::Allocator> allocator =
            std::make_unique<dts::LinearAllocator>(gb);

        for (auto i = 0uz; i < kb; ++i) {
            vector[i] = allocator->allocate(mb);
        }

        benchmark::DoNotOptimize(vector);
    }
}

BENCHMARK(test_v1);

BENCHMARK(test_v2);

int main() {
    dts::LinearAllocator allocator(1 << 10);

    allocator.show(std::cout);

    allocator.allocate(1, 1);
    allocator.show(std::cout);

    allocator.allocate(2, 2);
    allocator.show(std::cout);

    allocator.allocate(4, 4);
    allocator.show(std::cout);

    allocator.allocate(8, 8);
    allocator.show(std::cout);

    benchmark::RunSpecifiedBenchmarks();
}
