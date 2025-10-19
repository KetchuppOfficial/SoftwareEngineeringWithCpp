find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include(GoogleTest)

foreach(component intersection bounding_box)
    add_executable(${component}_tests src/${component}.cpp)
    target_link_libraries(${component}_tests
    PRIVATE
        rectangle
        GTest::GTest
        GTest::gtest_main
    )
    gtest_discover_tests(${component}_tests)
endforeach()
