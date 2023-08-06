#pragma once

#include <concepts>
#include <cstdlib>
#include <type_traits>

namespace ml {
namespace meta {

template <size_t... Is>
struct sequence {};

namespace detail {

template <size_t N, size_t... Is>
constexpr auto make_index_sequence_impl() {
  if constexpr (N == 0)
    return sequence<Is...>{};
  else
    return make_index_sequence_impl<N - 1, N - 1, Is...>();
}

template <size_t N, size_t V, size_t... Is>
constexpr auto make_repeat_sequence_impl() {
  if constexpr (N == 0)
    return sequence<Is...>{};
  else
    return make_repeat_sequence_impl<N - 1, V, V, Is...>();
};

template <size_t H, size_t L, size_t... Is>
constexpr auto make_range_sequence_impl() {
  if constexpr (H == L)
    return sequence<Is...>{};
  else
    return make_range_sequence_impl<H - 1, L, H - 1, Is...>();
};

template <size_t S, size_t N, template <typename, typename> class P, typename T,
          typename Ta, typename... Ts, size_t... Is>
constexpr auto make_satisfy_sequence_impl(sequence<Is...>) {
  if constexpr (P<T, Ta>::value) {
    if constexpr (N == 0)
      return sequence<Is..., S - (N + 1)>{};
    else
      return make_satisfy_sequence_impl<S, N - 1, P, T, Ts...>(
          sequence<Is..., S - (N + 1)>{});
  } else {
    if constexpr (N == 0)
      return sequence<Is...>{};
    else
      return make_satisfy_sequence_impl<S, N - 1, P, T, Ts...>(
          sequence<Is...>{});
  }
}

template <size_t N, typename... Args>
constexpr auto total_equals = (sizeof...(Args) == N);

template <typename T, typename... Args>
constexpr auto count_same = ((... + (std::same_as<T, Args> ? 1 : 0)));

template <template <typename, typename> class P, typename T, typename... Ts>
using all_satisfy = std::conjunction<P<T, Ts>...>;

template <template <typename, typename> class Pa, typename Ta,
          template <typename, typename> class Pb, typename Tb, typename... Ts>
using all_either =
    std::conjunction<std::disjunction<Pa<Ta, Ts>, Pb<Tb, Ts>>...>;

template <typename T, typename... Ts>
using all_same = all_satisfy<std::is_same, T, Ts...>;

template <size_t N>
using index_sequence_t = decltype(detail::make_index_sequence_impl<N>());

template <size_t N>
constexpr auto index_sequence = index_sequence_t<N>{};

template <size_t N, size_t V>
using repeat_sequence_t = decltype(detail::make_repeat_sequence_impl<N, V>());

template <size_t N, size_t V>
constexpr auto repeat_sequence = repeat_sequence_t<N, V>{};

template <size_t L, size_t H>
using range_sequence_t = decltype(detail::make_range_sequence_impl<H, L>());

template <size_t L, size_t H>
constexpr auto range_sequence = range_sequence_t<L, H>{};

template <template <typename, typename> class P, typename T, typename... Ts>
using satisfy_sequence_t =
    decltype(make_satisfy_sequence_impl<sizeof...(Ts), sizeof...(Ts) - 1, P, T,
                                        Ts...>(sequence{}));

template <template <typename, typename> class P, typename T, typename... Ts>
constexpr auto satisfy_sequence = satisfy_sequence_t<P, T, Ts...>{};
};  // namespace detail

using detail::all_satisfy, detail::all_either, detail::all_same;
using detail::index_sequence_t, detail::index_sequence;
using detail::range_sequence_t, detail::range_sequence;
using detail::repeat_sequence_t, detail::repeat_sequence;
using detail::satisfy_sequence_t, detail::satisfy_sequence;
using detail::total_equals, detail::count_same;

};  // namespace meta
};  // namespace ml