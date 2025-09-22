cmake_minimum_required(VERSION 3.20)

project(quadratic-equation-solver
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME}
PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)
