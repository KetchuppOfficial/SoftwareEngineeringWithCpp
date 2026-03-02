find_package(benchmark REQUIRED)

add_executable(sort-benchmark src/sort.cpp)
target_link_libraries(sort-benchmark
PRIVATE
    sort
    benchmark::benchmark
)
