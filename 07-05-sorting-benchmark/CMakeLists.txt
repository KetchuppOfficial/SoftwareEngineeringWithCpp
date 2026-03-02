cmake_minimum_required(VERSION 3.23)

project(sorting_benchmark
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(sort INTERFACE)
target_sources(sort INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES include/sort.hpp
)
target_compile_options(sort
INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)

add_subdirectory(benchmark)
