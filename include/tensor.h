#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <valarray>

namespace ml {
namespace types {

namespace detail {

template <size_t N>
class tensor_traits {
 public:
  using array_type = std::array<size_t, N>;

  static constexpr auto rank = N;

  const array_type dimensions;
  const array_type strides;
  const size_t size;

  tensor_traits(const array_type dim, const array_type strd)
      : dimensions(dim), strides(strd), size(dim[0] * strd[0]){};

  tensor_traits(const array_type dim)
      : tensor_traits(dim, calculate_strides(dim)){};

  template <typename... Args>
    requires std::conjunction_v<meta::total_equals<N, Args...>,
                                meta::all_convertible<size_t, Args...>>
  auto calculate_offset(Args&&... args) {
    array_type vals = {args...};

    auto overflows =
        std::inner_product(vals.begin(), vals.end(), dimensions.begin(), 0,
                           std::plus{}, std::greater_equal{});

    if (overflows > 0) throw std::out_of_range("tensor access out of range");

    return std::inner_product(vals.begin(), vals.end(), strides.begin(), 0);
  };

  operator std::gslice() {
    return {0, {dimensions.data(), N}, {strides.data(), N}};
  };

 private:
  static constexpr array_type calculate_strides(const array_type& dim) {
    array_type strides;

    strides.back() = 1;
    std::transform(dim.rbegin(), dim.rend() - 1, strides.rbegin(),
                   strides.rbegin() + 1, std::multiplies{});

    return strides;
  };
};

template <typename T, size_t N>
class tensor {
 public:
  using trait_type = tensor_traits<N>;
  using container_type = std::valarray<T>;
  using value_type = container_type::value_type;

  static constexpr auto rank = trait_type::rank;

  template <typename... Args>
    requires std::constructible_from<T, Args...>
  tensor(const std::array<size_t, N> dim, Args&&... args)
      : tensor(dim, T{std::forward<Args>(args)...}){};

  tensor(const std::array<size_t, N> dim, T& init)
      : _traits(dim), _container(init, _traits.size()){};

 private:
  trait_type _traits;
  container_type _container;
};

}  // namespace detail

}  // namespace types
}  // namespace ml