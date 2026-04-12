#include <iostream>
#include <vector>

#include <benchmark/benchmark.h>

#include "list_allocator.hpp"

static constexpr std::size_t kDummy = 0;

void test_v1(benchmark::State &state) {
    auto kb = 1uz << 10, mb = 1uz << 20;

    std::vector<void *> vector(kb, nullptr);

    for (auto element : state) {
        for (auto i = 0uz; i < kb; ++i) {
            vector[i] = operator new(mb);
        }

        for (auto i = 0uz; i < kb; i += 2) {
            operator delete(vector[i], mb);
        }

        for (auto i = 0uz; i < kb; i += 2) {
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
            std::make_unique<dts::ListAllocator>(gb, mb);

        for (auto i = 0uz; i < kb; ++i) {
            vector[i] = allocator->allocate(kDummy);
        }

        for (auto i = 0uz; i < kb; i += 2) {
            allocator->deallocate(vector[i], kDummy);
        }

        for (auto i = 0uz; i < kb; i += 2) {
            vector[i] = allocator->allocate(kDummy);
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
    dts::ListAllocator allocator(32, 8);

    allocator.show(std::cout);
    allocator.allocate(kDummy);

    allocator.show(std::cout);
    auto x = allocator.allocate(kDummy);

    allocator.show(std::cout);
    auto y = allocator.allocate(kDummy);

    allocator.show(std::cout);
    allocator.allocate(kDummy);

    allocator.show(std::cout);
    allocator.allocate(kDummy);

    allocator.show(std::cout);
    allocator.deallocate(x, kDummy);

    allocator.show(std::cout);
    allocator.deallocate(y, kDummy);

    allocator.show(std::cout);
    auto z = allocator.allocate(kDummy);

    allocator.show(std::cout);

    assert(z == y);

    benchmark::RunSpecifiedBenchmarks();
}
