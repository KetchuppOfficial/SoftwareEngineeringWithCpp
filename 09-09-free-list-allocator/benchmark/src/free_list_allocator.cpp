#include <cstddef>
#include <iostream>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

#include "free_list_allocator.hpp"

static constexpr auto kKB = 1uz << 10;
static constexpr auto kMB = 1uz << 20;
static constexpr auto kGB = 1uz << 30;

static void without_allocator(benchmark::State &state) {
    std::uniform_int_distribution distribution(1, 16);
    std::default_random_engine engine;
    std::vector<std::pair<void *, std::size_t>> vector(kKB);

    for (auto element : state) {
        for (auto i = 0uz; i < kKB; ++i) {
            vector[i].second = distribution(engine) * kMB;
            vector[i].first = operator new(vector[i].second);
        }

        for (auto i = 0uz; i < kKB; i += 4) {
            operator delete(vector[i].first, vector[i].second);
        }

        for (auto i = 0uz; i < kKB; i += 4) {
            vector[i].second = distribution(engine) * kMB;
            vector[i].first = operator new(vector[i].second);
        }

        for (auto i = 0uz; i < kKB; ++i) {
            operator delete(vector[i].first, vector[i].second);
        }

        benchmark::DoNotOptimize(vector);
    }
}

template <dts::FreeListAllocator::SearchPolicy SearchPolicy>
static void find(benchmark::State &state) {
    std::uniform_int_distribution distribution(1, 16);
    std::default_random_engine engine;
    std::vector<void *> vector(kKB, nullptr);

    for (auto element : state) {
        dts::FreeListAllocator allocator(16 * kGB, SearchPolicy);

        for (auto i = 0uz; i < kKB; ++i) {
            vector[i] = allocator.allocate(distribution(engine) * kMB);
        }

        for (auto i = 0uz; i < kKB; i += 4) {
            allocator.deallocate(vector[i]);
        }

        for (auto i = 0uz; i < kKB; i += 4) {
            vector[i] = allocator.allocate(distribution(engine) * kMB);
        }

        for (auto i = 0uz; i < kKB; ++i) {
            allocator.deallocate(vector[i]);
        }

        benchmark::DoNotOptimize(vector);
    }
}

BENCHMARK(without_allocator);
BENCHMARK(find<dts::FreeListAllocator::SearchPolicy::first>);
BENCHMARK(find<dts::FreeListAllocator::SearchPolicy::best>);

int main() {
    dts::FreeListAllocator allocator(1 << 10, dts::FreeListAllocator::SearchPolicy::first);

    allocator.show(std::cout);
    allocator.allocate(16);

    allocator.show(std::cout);
    auto x = allocator.allocate(16);

    allocator.show(std::cout);
    auto y = allocator.allocate(16);

    allocator.show(std::cout);
    allocator.allocate(16);

    allocator.show(std::cout);
    allocator.deallocate(y);

    allocator.show(std::cout);
    allocator.deallocate(x);

    allocator.show(std::cout);
    auto z = allocator.allocate(32);

    allocator.show(std::cout);

    assert(z == x);

    benchmark::RunSpecifiedBenchmarks();
}
