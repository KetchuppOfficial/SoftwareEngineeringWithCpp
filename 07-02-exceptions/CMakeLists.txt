cmake_minimum_required(VERSION 3.23)

project(rational_with_exceptions
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
    FILES
        include/rational.hpp
        include/exception.hpp
)
target_link_libraries(${PROJECT_NAME} INTERFACE operators)

add_executable(bad_alloc src/bad_alloc.cpp)
add_executable(bad_optional_access src/bad_optional_access.cpp)
add_executable(bad_variant_access src/bad_variant_access.cpp)
add_executable(length_error src/length_error.cpp)
add_executable(out_of_range src/out_of_range.cpp)

enable_testing()
add_subdirectory(test)
