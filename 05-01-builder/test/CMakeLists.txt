find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include(GoogleTest)

add_executable(${PROJECT_NAME}_tests src/builder.cpp)
target_link_libraries(${PROJECT_NAME}_tests
PRIVATE
    ${PROJECT_NAME}
    GTest::GTest
    GTest::gtest_main
)
gtest_discover_tests(${PROJECT_NAME}_tests)
