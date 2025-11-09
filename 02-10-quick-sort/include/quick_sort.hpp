#ifndef INCLUDE_QUICK_SORT_HPP
#define INCLUDE_QUICK_SORT_HPP

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>

namespace dts {

namespace detail {

template <std::random_access_iterator It, typename Compare>
void insertion_sort(It first, It last, Compare comp) {
    for (auto i = std::next(first); i != last; ++i) {
        for (auto j = i; j != first; --j) {
            if (auto before_j = std::prev(j); comp(*j, *before_j)) {
                std::iter_swap(j, before_j);
            }
        }
    }
}

template <std::random_access_iterator It, typename Compare>
It pivot(It first, It last, Compare comp) {
    assert(first != last);

    auto mid_it = std::next(first, std::distance(first, last) / 2);
    --last;

    if (comp(*mid_it, *first)) {
        std::iter_swap(mid_it, first);
    }
    if (comp(*last, *first)) {
        std::iter_swap(last, first);
    }
    if (comp(*mid_it, *last)) {
        std::iter_swap(mid_it, last);
    }

    return last;
}

template <std::random_access_iterator It, typename Compare>
It partition(It first, It last, Compare comp) {
    assert(first != last);

    auto pivot_it = ::dts::detail::pivot(first, last, comp);
    --last;
    auto i = first;
    for (auto it = first; it != last; ++it) {
        if (!comp(*pivot_it, *it)) {
            std::iter_swap(i, it);
            ++i;
        }
    }
    std::iter_swap(i, last);
    return i;
}

} // namespace detail

template <std::random_access_iterator It, typename Compare>
void sort(It first, It last, Compare comp) {
    if (first >= last) {
        return;
    }

    constexpr std::ptrdiff_t kQuickSortThreshold = 16;
    if (std::distance(first, last) >= kQuickSortThreshold) {
        auto q = ::dts::detail::partition(first, last, comp);
        ::dts::sort(first, q, comp);
        ::dts::sort(std::next(q), last, comp);
    } else {
        ::dts::detail::insertion_sort(first, last, comp);
    }
}

template <std::random_access_iterator It>
void sort(It first, It last) {
    sort(first, last, std::less{});
}

} // namespace dts

#endif // INCLUDE_QUICK_SORT_HPP
