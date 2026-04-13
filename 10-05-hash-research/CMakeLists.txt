cmake_minimum_required(VERSION 3.23)

project(hash_research
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CLI11 REQUIRED)

add_library(hash INTERFACE)
target_sources(hash INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES include/hash.hpp
)
target_compile_options(hash
INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)

add_executable(stats src/main.cpp)
target_link_libraries(stats
PRIVATE
    CLI11::CLI11
    hash
)
