# Call tracer

## How to build

1) Without tracing

    ```bash
    cmake -B build-release -DCMAKE_BUILD_TYPE=Release
    ```

2) With tracing

    ```bash
    cmake -B build-debug -DCMAKE_BUILD_TYPE=Debug
    ```

## How to run

1) Without tracing

    ```bash
    build-release/tracer
    # 7! == 5040
    ```

2) With tracing

    ```bash
    build-debug/tracer
    # Entering 'int main()' { file: ... 09-01-tracer/src/main.cpp:11:5 }
    # Entering 'main()::<lambda()>' { file: ... 09-01-tracer/src/main.cpp:14:9 }
    # Entering 'unsigned int factorial(unsigned int)' { file: ... 09-01-tracer/src/main.cpp:6:5 }
    # Entering 'unsigned int factorial(unsigned int)' { file: ... 09-01-tracer/src/main.cpp:6:5 }
    # Entering 'unsigned int factorial(unsigned int)' { file: ... 09-01-tracer/src/main.cpp:6:5 }
    # Entering 'unsigned int factorial(unsigned int)' { file: ... 09-01-tracer/src/main.cpp:6:5 }
    # Entering 'unsigned int factorial(unsigned int)' { file: ... 09-01-tracer/src/main.cpp:6:5 }
    # Entering 'unsigned int factorial(unsigned int)' { file: ... 09-01-tracer/src/main.cpp:6:5 }
    # Entering 'unsigned int factorial(unsigned int)' { file: ... 09-01-tracer/src/main.cpp:6:5 }
    # Exiting
    # Exiting
    # Exiting
    # Exiting
    # Exiting
    # Exiting
    # Exiting
    # Exiting
    # 7! == 5040
    # Exiting
    ```
