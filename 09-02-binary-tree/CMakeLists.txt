cmake_minimum_required(VERSION 3.23)

project(binary_tree
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(WITH_SANITIZERS "Turn on sanitizers")

set(is_gcc_or_clang "$<CXX_COMPILER_ID:GNU,Clang>")

add_library(${PROJECT_NAME}_lib INTERFACE)
target_sources(${PROJECT_NAME}_lib INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES include/binary_tree.hpp
)
target_compile_options(${PROJECT_NAME}_lib
INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<${is_gcc_or_clang}: -Wall -Wextra -pedantic>
)

set(SANITIZER_OPTIONS
    $<$<AND:$<BOOL:${WITH_SANITIZERS}>,${is_gcc_or_clang}>:-fsanitize=address,undefined,leak>)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
target_compile_options(${PROJECT_NAME} PRIVATE ${SANITIZER_OPTIONS})
target_link_options(${PROJECT_NAME} PRIVATE ${SANITIZER_OPTIONS})
