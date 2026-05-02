#ifndef INCLUDE_TRANSFORM_IF_HPP
#define INCLUDE_TRANSFORM_IF_HPP

#include <algorithm>
#include <concepts>
#include <functional>
#include <iterator>
#include <ranges>
#include <utility>

namespace dts {

namespace ranges {

template <typename I, typename O>
using transform_if_result = std::ranges::in_out_result<I, O>;

struct transform_if_fn {
    template <std::input_iterator I, std::sentinel_for<I> S, std::weakly_incrementable O,
              std::copy_constructible F, class Proj = std::identity,
              std::indirect_unary_predicate<std::projected<I, Proj>> Pred>
        requires std::indirectly_writable<O, std::indirect_result_t<F &, std::projected<I, Proj>>>
    constexpr transform_if_result<I, O> operator()(I first, S last, O result, F op, Pred pred,
                                                   Proj proj = {}) const {
        for (; first != last; ++first) {
            auto &&projected = std::invoke(proj, *first);
            if (std::invoke(pred, projected)) {
                *result = std::invoke(op, std::forward<decltype(projected)>(projected));
                ++result;
            }
        }

        return {std::move(first), std::move(result)};
    }

    template <std::ranges::input_range R, std::weakly_incrementable O, std::copy_constructible F,
              class Proj = std::identity,
              std::indirect_unary_predicate<std::projected<std::ranges::iterator_t<R>, Proj>> Pred>
        requires std::indirectly_writable<
            O, std::indirect_result_t<F &, std::projected<std::ranges::iterator_t<R>, Proj>>>
    constexpr transform_if_result<std::ranges::borrowed_iterator_t<R>, O>
    operator()(R &&r, O result, F op, Pred pred, Proj proj = {}) const {
        return (*this)(std::ranges::begin(r), std::ranges::end(r), std::move(result), std::move(op),
                       std::move(pred), std::move(proj));
    }
};

inline constexpr transform_if_fn transform_if;

} // namespace ranges

} // namespace dts

#endif // INCLUDE_TRANSFORM_IF_HPP
