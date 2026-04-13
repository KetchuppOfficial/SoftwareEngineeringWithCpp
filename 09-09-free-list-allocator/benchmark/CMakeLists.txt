find_package(benchmark REQUIRED)

add_executable(${PROJECT_NAME}_benchmark src/${PROJECT_NAME}.cpp)
set_target_properties(${PROJECT_NAME}_benchmark
PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
)
target_link_libraries(${PROJECT_NAME}_benchmark
PRIVATE
    ${PROJECT_NAME}
    benchmark::benchmark
)
