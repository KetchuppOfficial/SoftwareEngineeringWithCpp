find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include(GoogleTest)

foreach(lib ${LIBS})
    add_executable(${lib}_tests src/${lib}.cpp)
    target_link_libraries(${lib}_tests
    PRIVATE
        ${lib}
        GTest::gtest_main
        GTest::gmock
    )
    gtest_discover_tests(${lib}_tests)
endforeach()