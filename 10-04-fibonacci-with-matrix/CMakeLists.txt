cmake_minimum_required(VERSION 3.23)

project(fibonacci_with_matrix
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost CONFIG REQUIRED COMPONENTS headers)
find_package(CLI11 REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME}
PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)
target_link_libraries(${PROJECT_NAME}
PRIVATE
    Boost::headers
    CLI11::CLI11
)
