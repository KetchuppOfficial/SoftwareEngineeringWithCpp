cmake_minimum_required(VERSION 3.23)

project(ranges_and_views
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(options INTERFACE)
target_compile_options(options
INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)

foreach(target transform_if mae mse fibonacci_view)
    add_library(${target} INTERFACE)
    target_sources(${target} INTERFACE
        FILE_SET HEADERS
        BASE_DIRS include
        FILES include/${target}.hpp
    )
    target_link_libraries(${target} INTERFACE options)
endforeach()

foreach(target replace fill unique rotate sample filter drop join zip stride)
    add_executable(${target} src/${target}.cpp)
    target_link_libraries(${target} PRIVATE options)
endforeach()

enable_testing()
add_subdirectory(test)
