cmake_minimum_required(VERSION 3.23)

project(file_calculator
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost CONFIG REQUIRED COMPONENTS headers)

set(targets recursive_descent spirit)

foreach(target ${targets})
    add_executable(${target} src/${target}.cpp)
    target_compile_options(${target}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/Wall>
        $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
    )
endforeach()

target_link_libraries(spirit PRIVATE Boost::headers)
