find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include(GoogleTest)

foreach(algorithm gcd lcm)
    add_executable(${algorithm}_tests src/${algorithm}.cpp)
    target_link_libraries(${algorithm}_tests
    PRIVATE
        ${algorithm}
        GTest::GTest
        GTest::gtest_main
    )
    gtest_discover_tests(${algorithm}_tests)
endforeach()
