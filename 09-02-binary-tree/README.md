# Binary tree with smart pointers

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
    build-with-sanitizers/binary_tree
    # DFS: 1245367
    # BFS: 1234567
    ```

2) Without sanitizers

    ```bash
    valgrind build-without-sanitizers/binary_tree
    # ==128718== Memcheck, a memory error detector
    # ==128718== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
    # ==128718== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
    # ==128718== Command: build/binary_tree
    # ==128718==
    # DFS: 1245367
    # BFS: 1234567
    # ==128718==
    # ==128718== HEAP SUMMARY:
    # ==128718==     in use at exit: 0 bytes in 0 blocks
    # ==128718==   total heap usage: 11 allocs, 11 frees, 75,832 bytes allocated
    # ==128718==
    # ==128718== All heap blocks were freed -- no leaks are possible
    # ==128718==
    # ==128718== For lists of detected and suppressed errors, rerun with: -s
    # ==128718== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
    ```
