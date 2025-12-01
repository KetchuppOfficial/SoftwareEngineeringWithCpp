cmake_minimum_required(VERSION 3.20)

project(template_fibonacci
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLES ${PROJECT_NAME} ${PROJECT_NAME}_fail_overflow)

foreach(exe ${EXECUTABLES})
    add_executable(${exe} src/main.cpp)
    target_include_directories(${exe} PRIVATE include)
    target_compile_options(${exe}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/Wall>
        $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
    )
endforeach()

target_compile_definitions(${PROJECT_NAME}_fail_overflow PRIVATE FIBONACCI_OVERFLOW)
