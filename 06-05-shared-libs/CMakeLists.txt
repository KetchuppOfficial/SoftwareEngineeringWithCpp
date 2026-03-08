cmake_minimum_required(VERSION 3.23)

project(dlopen
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.87 REQUIRED COMPONENTS filesystem)

foreach(lib shared1 shared2)
    add_library(${lib} SHARED lib/${lib}.cpp)
    target_include_directories(${lib} PUBLIC include)
    target_compile_options(${lib}
    PUBLIC
        $<$<CXX_COMPILER_ID:MSVC>:/Wall>
        $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
    )
endforeach()

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::filesystem)
target_compile_options(${PROJECT_NAME}
PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
)
