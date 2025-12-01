# Compile-time fibonacci numbers using recursive templates

## Building version without overflow

```bash
cmake --build build --target template_fibonacci
```

Successful compilation indicates that all static asserts passed.

## Building version with overflow

```bash
cmake --build build --target template_fibonacci_fail_overflow
```

Compilation will fail with message like the following:

```bash
In file included from /software-engineering-in-cpp/04-05-template-fibonacci/src/main.cpp:1:
/software-engineering-in-cpp/04-05-template-fibonacci/include/fibonacci.hpp: In instantiation of ‘struct dts::fib<47>’:
/software-engineering-in-cpp/04-05-template-fibonacci/include/fibonacci.hpp:27:32:   required from ‘constexpr const auto dts::fib_v<47>’
   27 | constexpr auto fib_v = fib<N>::value;
      |                                ^~~~~
/software-engineering-in-cpp/04-05-template-fibonacci/src/main.cpp:10:24:   required from here
   10 |     static_assert(dts::fib_v<47u> > 0);
      |                        ^~~~~~~~~~
/software-engineering-in-cpp/04-05-template-fibonacci/include/fibonacci.hpp:10:37: error: static assertion failed: Next Fibonacci number overflows int
   10 |     static_assert(fib<N - 1>::value <= std::numeric_limits<int>::max() - fib<N - 2>::value,
      |                               ~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```
