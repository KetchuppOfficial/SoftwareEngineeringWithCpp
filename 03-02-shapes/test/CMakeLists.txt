find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include(GoogleTest)

foreach(component circle square triangle)
    add_executable(${component}_tests src/${component}.cpp)
    target_link_libraries(${component}_tests
    PRIVATE
        ${PROJECT_NAME}
        GTest::GTest
        GTest::gtest_main
    )
    gtest_discover_tests(${component}_tests)
endforeach()
