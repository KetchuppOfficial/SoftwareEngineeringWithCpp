find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include(GoogleTest)

foreach(lib transform_if mae mse fibonacci_view)
    add_executable(${lib}_tests src/${lib}.cpp)
    target_link_libraries(${lib}_tests
    PRIVATE
        ${lib}
        GTest::GTest
        GTest::gtest_main
    )
    gtest_discover_tests(${lib}_tests)
endforeach()
