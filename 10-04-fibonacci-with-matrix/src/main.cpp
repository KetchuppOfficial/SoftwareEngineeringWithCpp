#include <print>

#include <CLI/CLI.hpp>

#include <boost/numeric/ublas/matrix.hpp>

namespace {

using Number = unsigned long long;
using Matrix = boost::numeric::ublas::matrix<Number>;

auto initial_matrix() {
    Matrix matrix(2, 2);
    matrix(0, 0) = 1;
    matrix(0, 1) = 1;
    matrix(1, 0) = 1;
    matrix(1, 1) = 0;
    return matrix;
}

auto eye() {
    Matrix matrix(2, 2);
    matrix(0, 0) = 1;
    matrix(0, 1) = 0;
    matrix(1, 0) = 0;
    matrix(1, 1) = 1;
    return matrix;
}

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

/*
 * ┌      ┐^n    ┌                 ┐
 * │ 1  1 │   == │ F_{n+1} F_n     │
 * │ 1  0 │      │ F_n     F_{n-1} │
 * └      ┘      └                 ┘
 */
Number fib(unsigned n) {
    if (n == 0) {
        return 0;
    }
    const auto res = pow(initial_matrix(), eye(), n);
    return res(0, 1);
}

} // unnamed namespace

int main(int argc, char **argv) {
    CLI::App app{"Compute Fibonacci numbers using matrix multiplication"};

    unsigned n{};
    app.add_option("--n", n, "Index of the Fibonacci number to compute")->required();

    CLI11_PARSE(app, argc, argv);

    std::println("fib({}) == {}", n, fib(n));
}
