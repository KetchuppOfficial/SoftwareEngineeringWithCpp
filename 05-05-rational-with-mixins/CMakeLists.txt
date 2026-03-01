cmake_minimum_required(VERSION 3.20)

project(rational_with_mixins
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(operators INTERFACE)
target_sources(operators INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES include/operators.hpp
)
target_compile_features(operators INTERFACE cxx_std_23)
target_compile_options(operators
INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES include/rational.hpp
)
target_link_libraries(${PROJECT_NAME} INTERFACE operators)

enable_testing()
add_subdirectory(test)
