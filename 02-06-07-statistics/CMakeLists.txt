cmake_minimum_required(VERSION 3.23)

project(statistics
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_link_libraries(${PROJECT_NAME} INTERFACE m)
target_compile_options(${PROJECT_NAME}
INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)

add_executable(with-array src/with-array.cpp)
target_link_libraries(with-array PRIVATE ${PROJECT_NAME})

add_executable(with-vector src/with-vector.cpp)
target_link_libraries(with-vector PRIVATE ${PROJECT_NAME})
