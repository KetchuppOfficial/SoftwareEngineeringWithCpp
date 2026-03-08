cmake_minimum_required(VERSION 3.23)

project(timer
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(libtimer INTERFACE)
target_sources(libtimer INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES include/timer.hpp
)
target_compile_options(libtimer
INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
PRIVATE
    libtimer
    m
)
