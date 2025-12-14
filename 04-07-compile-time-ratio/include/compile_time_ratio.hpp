#ifndef INCLUDE_COMPILE_TIME_RATION_HPP
#define INCLUDE_COMPILE_TIME_RATION_HPP

#include <numeric>
#include <utility>

namespace dts {

// -------------------------------------------------------------------------------------------------

namespace detail {

consteval std::pair<int, int> reduce(int num, int den) {
    if (den < 0) {
        num = -num;
        den = -den;
    }

    auto gcd = std::gcd(num, den);
    num /= gcd;
    den /= gcd;

    return {num, den};
}

} // namespace detail

template <int N = 0, int D = 1>
struct Ratio {
    static_assert(D != 0, "denominator shall no be equal to 0");

  private:
    static constexpr auto num_den = detail::reduce(N, D);

  public:
    constexpr static auto num = num_den.first;
    constexpr static auto den = num_den.second;
};

// ------------------------------------------------------------------------------------------------

template <typename R1, typename R2>
struct Sum {
  private:
    constexpr static auto num_den =
        detail::reduce(R1::num * R2::den + R2::num * R1::den, R1::den *R2::den);

  public:
    using type = Ratio<num_den.first, num_den.second>;
};

template <typename R1, typename R2>
using sum = typename Sum<R1, R2>::type;

// -------------------------------------------------------------------------------------------------

template <typename R1, typename R2>
struct Sub {
    using type = typename Sum<R1, Ratio<-R2::num, R2::den>>::type;
};

template <typename R1, typename R2>
using sub = typename Sub<R1, R2>::type;

// -------------------------------------------------------------------------------------------------

template <typename R1, typename R2>
struct Mul {
  private:
    constexpr static auto num_den = detail::reduce(R1::num * R2::num, R1::den *R2::den);

  public:
    using type = Ratio<num_den.first, num_den.second>;
};

template <typename R1, typename R2>
using mul = typename Mul<R1, R2>::type;

// -------------------------------------------------------------------------------------------------

template <typename R1, typename R2>
struct Div {
    // no need for static_assert here, because there is one inside Ratio
    using type = typename Mul<R1, Ratio<R2::den, R2::num>>::type;
};

template <typename R1, typename R2>
using div = typename Div<R1, R2>::type;

// -------------------------------------------------------------------------------------------------

} // namespace dts

#endif // INCLUDE_COMPILE_TIME_RATION_HPP
