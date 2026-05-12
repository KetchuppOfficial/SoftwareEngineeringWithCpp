cmake_minimum_required(VERSION 3.23)

project(bytes_string_conversions
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBS bytes_to_string string_to_bytes)

foreach(lib ${LIBS})
    add_library(${lib} INTERFACE)
    target_sources(${lib} INTERFACE
        FILE_SET HEADERS
        BASE_DIRS include
        FILES include/${lib}.hpp
    )
    target_compile_options(${lib}
    INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/Wall>
        $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
    )
endforeach()

enable_testing()
add_subdirectory(test)
