cmake_minimum_required(VERSION 3.20)

project(shapes
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE
FILE_SET
    HEADERS
BASE_DIRS
    include
FILES
    include/circle.hpp
    include/square.hpp
    include/triangle.hpp
)
target_compile_options(${PROJECT_NAME}
INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)
target_link_libraries(${PROJECT_NAME} INTERFACE m)

enable_testing()
add_subdirectory(test)
