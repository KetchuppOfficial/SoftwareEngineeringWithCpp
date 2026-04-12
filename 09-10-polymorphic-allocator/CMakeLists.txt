cmake_minimum_required(VERSION 3.23)

project(polymorphic_allocator
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(allocators INTERFACE)
target_sources(allocators INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        include/allocator_base.hpp
        include/free_list_allocator.hpp
        include/linear_allocator.hpp
        include/list_allocator.hpp
        include/stack_allocator.hpp
)
target_compile_options(allocators
INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)

add_subdirectory(benchmark)
