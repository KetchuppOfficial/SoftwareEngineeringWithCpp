# Fibonacci numbers with matrix multiplication

## Simple loop-based algorithm

```C++
unsigned long long fib(unsigned n) {
    if (n < 2) {
        return n;
    }

    unsigned long long first = 1;
    unsigned long long second = 2;
    while (--n != 1) {
        first = std::exchange(second, first + second);
    }

    return first;
}
```

Complexity of is $O(n)$.

## Algorithm that uses matrix multiplication

Since matrix multiplication is implemented as follows, the complexity of raising a matrix to the
power $N$ is $\log_{2}(N)$.

```C++
Matrix pow(Matrix m, Matrix init, unsigned n) {
    if (n == 1) {
        return m;
    }

    while (n > 0) {
        if ((n & 0x1u) == 0x1u) {
            init = boost::numeric::ublas::prod(init, m);
            n -= 1;
        }
        m = boost::numeric::ublas::prod(m, m);
        n /= 2;
    }

    return init;
}
```
