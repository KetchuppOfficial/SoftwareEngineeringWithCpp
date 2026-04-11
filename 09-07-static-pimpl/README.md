# Static PImpl

## How to build

1) With sanitizers

    ```bash
    cmake -B build-with-sanitizers -DCMAKE_BUILD_TYPE=Release -DWITH_SANITIZERS=ON
    cmake --build build-with-sanitizers
    ```

2) Without sanitizers

    ```bash
    cmake -B build-without-sanitizers -DCMAKE_BUILD_TYPE=Release
    cmake --build build-without-sanitizers
    ```

## How to run

1) With sanitizers

    ```bash
    ctest --test-dir build-with-sanitizers
    # Test project software-engineering-in-cpp/09-07-static-pimpl/build-with-sanitizers
    # Start 1: StaticPimpl.DefaultConstructed
    # 1/3 Test #1: StaticPimpl.DefaultConstructed ...   Passed    0.05 sec
    #     Start 2: StaticPimpl.MoveConstructed
    # 2/3 Test #2: StaticPimpl.MoveConstructed ......   Passed    0.04 sec
    #     Start 3: StaticPimpl.MoveAssigned
    # 3/3 Test #3: StaticPimpl.MoveAssigned .........   Passed    0.03 sec
    #
    # 100% tests passed, 0 tests failed out of 3
    #
    # Total Test time (real) =   0.12 sec
    ```

2) Without sanitizers

    ```bash
    valgrind ctest --test-dir build-without-sanitizers
    # ==80763== Memcheck, a memory error detector
    # ==80763== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
    # ==80763== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
    # ==80763== Command: ctest --test-dir build-without-sanitizers
    # ==80763==
    # Test project software-engineering-in-cpp/09-07-static-pimpl/build-without-sanitizers
    #     Start 1: StaticPimpl.DefaultConstructed
    # 1/3 Test #1: StaticPimpl.DefaultConstructed ...   Passed    0.10 sec
    #     Start 2: StaticPimpl.MoveConstructed
    # 2/3 Test #2: StaticPimpl.MoveConstructed ......   Passed    0.02 sec
    #     Start 3: StaticPimpl.MoveAssigned
    # 3/3 Test #3: StaticPimpl.MoveAssigned .........   Passed    0.03 sec
    #
    # 100% tests passed, 0 tests failed out of 3
    #
    # Total Test time (real) =   0.80 sec
    # ==80763==
    # ==80763== HEAP SUMMARY:
    # ==80763==     in use at exit: 0 bytes in 0 blocks
    # ==80763==   total heap usage: 7,046 allocs, 7,046 frees, 2,252,984 bytes allocated
    # ==80763==
    # ==80763== All heap blocks were freed -- no leaks are possible
    # ==80763==
    # ==80763== For lists of detected and suppressed errors, rerun with: -s
    # ==80763== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    ```
