cmake_minimum_required(VERSION 3.23)

project(siamese_twins
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE
FILE_SET
    HEADERS
BASE_DIRS
    include
FILES
    include/client.hpp
    include/entity_v1.hpp
    include/entity_v2.hpp
)
target_compile_options(${PROJECT_NAME}
INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)

enable_testing()
add_subdirectory(test)
