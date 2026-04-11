cmake_minimum_required(VERSION 3.23)

project(static_pimpl
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(WITH_SANITIZERS "Turn on sanitizers")

set(is_gcc_or_clang "$<CXX_COMPILER_ID:GNU,Clang>")
set(SANITIZER_OPTIONS
    $<$<AND:$<BOOL:${WITH_SANITIZERS}>,${is_gcc_or_clang}>:-fsanitize=address,undefined,leak>)

add_library(${PROJECT_NAME} STATIC lib/${PROJECT_NAME}.cpp)
target_sources(${PROJECT_NAME} PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
    FILES include/${PROJECT_NAME}.hpp
)
target_compile_options(${PROJECT_NAME}
PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang>: -Wall -Wextra -pedantic>
    ${SANITIZER_OPTIONS}
)
target_link_options(${PROJECT_NAME} PUBLIC ${SANITIZER_OPTIONS})

enable_testing()
add_subdirectory(test)
