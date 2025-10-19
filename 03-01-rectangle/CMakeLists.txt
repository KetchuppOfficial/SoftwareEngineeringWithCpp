cmake_minimum_required(VERSION 3.20)

project(rectangles
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(rectangle INTERFACE)
target_sources(rectangle INTERFACE
FILE_SET
    HEADERS
BASE_DIRS
    include
FILES
    include/rectangle.hpp
)
target_compile_options(rectangle
INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)

enable_testing()
add_subdirectory(test)
