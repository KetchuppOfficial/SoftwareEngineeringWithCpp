find_package(benchmark REQUIRED)

foreach(allocator linear stack list free_list)
    add_executable(${allocator}_allocator_benchmark src/${allocator}_allocator.cpp)
    set_target_properties(${allocator}_allocator_benchmark
    PROPERTIES
        OUTPUT_NAME ${allocator}_allocator
    )
    target_link_libraries(${allocator}_allocator_benchmark
    PRIVATE
        allocators
        benchmark::benchmark
    )
endforeach()
