cmake_minimum_required(VERSION 3.20)

project(gcd-lcm
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(gcd STATIC lib/gcd.cpp)
add_library(lcm STATIC lib/lcm.cpp)

foreach(target gcd lcm)
    target_include_directories(${target} PUBLIC include)
    target_compile_options(${target}
    PUBLIC
        $<$<CXX_COMPILER_ID:MSVC>:/Wall>
        $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
    )
endforeach()

target_link_libraries(lcm PUBLIC gcd)

enable_testing()
add_subdirectory(test)
