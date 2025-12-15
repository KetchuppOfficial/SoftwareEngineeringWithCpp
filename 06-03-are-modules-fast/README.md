# Build time comparison for with same project with modules and without them

Both measurements were conducted in `for_modules` shell, which implies using `clang-21.1.2` as a
compiler and `Ninja` as a build system.

## Without modules

### Build from scratch

```bash
ketchupp@ketchupp:~/Programming/software-engineering-in-cpp/06-01-rational-project$ cmake -B build -DCMAKE_BUILD_TYPE=Release -G Ninja
-- The CXX compiler identification is Clang 21.1.2
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /nix/store/vn75s132n0i5yb5r1h7aiaphrfn7dwb4-clang-wrapper-21.1.2/bin/clang++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found GTest: /nix/store/qcwpp2qgwii2m1mshfj81ksmi2bcnszk-gtest-1.17.0-dev/lib/cmake/GTest/GTestConfig.cmake (found version "1.17.0")
-- Found Threads: TRUE
-- Configuring done (1.1s)
-- Generating done (0.0s)
-- Build files have been written to: /home/ketchupp/Programming/software-engineering-in-cpp/06-01-rational-project/build
ketchupp@ketchupp:~/Programming/software-engineering-in-cpp/06-01-rational-project$ time cmake --build build
[4/4] Linking CXX executable test/rational_tests

real	0m4,377s
user	0m5,728s
sys	0m0,556s
```

```text
4117ms test/CMakeFiles/rational_tests.dir/src/rational.cpp.o
1814ms CMakeFiles/rational.dir/lib/rational.cpp.o
179ms test/rational_tests
179ms test/rational_tests[1]_tests.cmake
179ms /home/ketchupp/Programming/software-engineering-in-cpp/06-01-rational-project/build/test/rational_tests[1]_tests.cmake
71ms librational.a
```

### Incremental build

One empty line was added to [rational.hpp](/03-10-rational/include/rational.hpp).

```bash
/software-engineering-in-cpp/06-01-rational-project$ time cmake --build build
[4/4] Linking CXX executable test/rational_tests

real	0m4,224s
user	0m5,595s
sys	0m0,544s
```

One empty line was added to [rational.cpp](/03-10-rational/lib/rational.cpp)

```bash
/software-engineering-in-cpp/06-01-rational-project$ time cmake --build build
[3/3] Linking CXX executable test/rational_tests

real	0m2,154s
user	0m1,829s
sys	0m0,318s
```

## With modules

### Build from scratch

```bash
/software-engineering-in-cpp/06-02-rational-with-modules$ cmake -Wno-dev -G Ninja -B build -DCMAKE_BUILD_TYPE=Release
-- The CXX compiler identification is Clang 21.1.2
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /nix/store/vn75s132n0i5yb5r1h7aiaphrfn7dwb4-clang-wrapper-21.1.2/bin/clang++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found GTest: /nix/store/qcwpp2qgwii2m1mshfj81ksmi2bcnszk-gtest-1.17.0-dev/lib/cmake/GTest/GTestConfig.cmake (found version "1.17.0")
-- Found Threads: TRUE
-- Configuring done (1.4s)
-- Generating done (0.0s)
-- Build files have been written to: /home/ketchupp/Programming/software-engineering-in-cpp/06-02-rational-with-modules/build
/software-engineering-in-cpp/06-02-rational-with-modules$ time cmake --build build
[16/16] Linking CXX executable test/rational_with_modules_tests

real	0m9,752s
user	0m9,498s
sys	0m1,485s
```

```text
5050ms CMakeFiles/__cmake_cxx23.dir/nix/store/w2gpy4chap9wx42gabzgcp002d7gwirk-libcxx-21.1.2/share/libc++/v1/std.cppm.o
5050ms CMakeFiles/__cmake_cxx23.dir/std.pcm
4145ms test/CMakeFiles/rational_with_modules_tests.dir/src/rational.cpp.o
525ms CMakeFiles/__cmake_cxx23.dir/nix/store/w2gpy4chap9wx42gabzgcp002d7gwirk-libcxx-21.1.2/share/libc++/v1/std.compat.cppm.o
525ms CMakeFiles/__cmake_cxx23.dir/std.compat.pcm
204ms CMakeFiles/__cmake_cxx23.dir/nix/store/w2gpy4chap9wx42gabzgcp002d7gwirk-libcxx-21.1.2/share/libc++/v1/std.cppm.o.ddi
200ms CMakeFiles/rational_with_modules.dir/src/rational.cpp.o
192ms test/rational_with_modules_tests
192ms test/rational_with_modules_tests[1]_tests.cmake
192ms /home/ketchupp/Programming/software-engineering-in-cpp/06-02-rational-with-modules/build/test/rational_with_modules_tests[1]_tests.cmake
177ms CMakeFiles/rational_with_modules.dir/modules/rational.cppm.o
177ms CMakeFiles/rational_with_modules.dir/rational.pcm
154ms test/CMakeFiles/rational_with_modules_tests.dir/src/rational.cpp.o.ddi
93ms CMakeFiles/__cmake_cxx23.dir/nix/store/w2gpy4chap9wx42gabzgcp002d7gwirk-libcxx-21.1.2/share/libc++/v1/std.compat.cppm.o.ddi
69ms lib__cmake_cxx23.a
65ms librational_with_modules.a
64ms CMakeFiles/rational_with_modules.dir/src/rational.cpp.o.ddi
63ms CMakeFiles/rational_with_modules.dir/modules/rational.cppm.o.ddi
25ms test/CMakeFiles/rational_with_modules_tests.dir/CXX.dd
25ms test/CMakeFiles/rational_with_modules_tests.dir/CXXModules.json
25ms test/CMakeFiles/rational_with_modules_tests.dir/src/rational.cpp.o.modmap
19ms CMakeFiles/rational_with_modules.dir/CXX.dd
19ms CMakeFiles/rational_with_modules.dir/CXXModules.json
19ms CMakeFiles/rational_with_modules.dir/src/rational.cpp.o.modmap
19ms CMakeFiles/rational_with_modules.dir/modules/rational.cppm.o.modmap
18ms CMakeFiles/__cmake_cxx23.dir/CXX.dd
18ms CMakeFiles/__cmake_cxx23.dir/CXXModules.json
18ms CMakeFiles/__cmake_cxx23.dir/nix/store/w2gpy4chap9wx42gabzgcp002d7gwirk-libcxx-21.1.2/share/libc++/v1/std.cppm.o.modmap
18ms CMakeFiles/__cmake_cxx23.dir/nix/store/w2gpy4chap9wx42gabzgcp002d7gwirk-libcxx-21.1.2/share/libc++/v1/std.compat.cppm.o.modmap
```

### Incremental build

One empty line was added to [rational.cppm](/06-02-rational-with-modules/modules/rational.cppm).

```bash
/software-engineering-in-cpp/06-02-rational-with-modules$ time cmake --build build
[7/7] Linking CXX executable test/rational_with_modules_tests

real	0m4,690s
user	0m4,359s
sys	0m0,614s
```

One empty line was added to [rational.cpp](/06-02-rational-with-modules/src/rational.cpp)

```bash
/software-engineering-in-cpp/06-02-rational-with-modules$ time cmake --build build
[5/5] Linking CXX executable test/rational_with_modules_tests

real	0m0,602s
user	0m0,324s
sys	0m0,280s

```

## Results

- The size of executables with tests is the same for both version and is 115K.
- Fresh build time for the version with modules is significantly greater due to the necessity to
analyze standard modules.
- Rebuilding implementation units is much faster than rebuilding source file with included headers.
- Link time almost did not change.

## Conclusion

Modules are slower for fresh builds but may be faster for incremental build. I believe, real
measurements should be conducted on big projects such as llvm. Sadly, it takes unreasonable amount
of time to modularize them.
