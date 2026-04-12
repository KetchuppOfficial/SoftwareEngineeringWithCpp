#include <cstddef>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include <benchmark/benchmark.h>

#include "free_list_allocator.hpp"

static constexpr std::size_t kDummy = 0;

void test_v1(benchmark::State &state) {
    auto kb = 1uz << 10, mb = 1uz << 20;

    std::uniform_int_distribution distribution(1, 16);

    std::default_random_engine engine;

    std::vector<std::pair<void *, std::size_t>> vector(kb);

    for (auto element : state) {
        for (auto i = 0uz; i < kb; ++i) {
            vector[i].second = distribution(engine) * mb;

            vector[i].first = operator new(vector[i].second);
        }

        for (auto i = 0uz; i < kb; i += 32) {
            operator delete(vector[i].first, vector[i].second);
        }

        for (auto i = 0uz; i < kb; i += 32) {
            vector[i].second = distribution(engine) * mb;

            vector[i].first = operator new(vector[i].second);
        }

        for (auto i = 0uz; i < kb; ++i) {
            operator delete(vector[i].first, vector[i].second);
        }

        benchmark::DoNotOptimize(vector);
    }
}

void test_v2(benchmark::State &state) {
    auto kb = 1uz << 10, mb = 1uz << 20, gb = 1uz << 30;

    std::uniform_int_distribution distribution(1, 16);

    std::default_random_engine engine;

    std::vector<void *> vector(kb, nullptr);

    for (auto element : state) {
        const std::unique_ptr<dts::Allocator> allocator =
            std::make_unique<dts::FreeListAllocator>(16 * gb);

        for (auto i = 0uz; i < kb; ++i) {
            vector[i] = allocator->allocate(distribution(engine) * mb);
        }

        for (auto i = 0uz; i < kb; i += 32) {
            allocator->deallocate(vector[i], kDummy);
        }

        for (auto i = 0uz; i < kb; i += 32) {
            vector[i] = allocator->allocate(distribution(engine) * mb);
        }

        for (auto i = 0uz; i < kb; ++i) {
            allocator->deallocate(vector[i], kDummy);
        }

        benchmark::DoNotOptimize(vector);
    }
}

BENCHMARK(test_v1);

BENCHMARK(test_v2);

int main() {
    dts::FreeListAllocator allocator(1 << 10);

    allocator.show(std::cout);
    allocator.allocate(16);

    allocator.show(std::cout);
    auto x = allocator.allocate(16);

    allocator.show(std::cout);
    auto y = allocator.allocate(16);

    allocator.show(std::cout);
    allocator.allocate(16);

    allocator.show(std::cout);
    allocator.deallocate(y, kDummy);

    allocator.show(std::cout);
    allocator.deallocate(x, kDummy);

    allocator.show(std::cout);
    auto z = allocator.allocate(32);

    allocator.show(std::cout);

    assert(z == x);

    benchmark::RunSpecifiedBenchmarks();
}
