cmake_minimum_required(VERSION 4.1.2)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)

project(rational_with_modules
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
target_sources(${PROJECT_NAME}
PUBLIC
    FILE_SET CXX_MODULES FILES modules/rational.cppm
PRIVATE
    src/rational.cpp
)
target_compile_options(${PROJECT_NAME}
PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)

enable_testing()
add_subdirectory(test)
