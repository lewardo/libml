#pragma once

#include <algorithm>
#include <concepts>
#include <ctime>
#include <execution>
#include <random>
#include <ranges>

#include "types.h"
#include "utils.h"

static constexpr double RAND_COEFF = RAND_MAX / 2;

namespace ml {
namespace random {

namespace detail {

using namespace types;

template <typename T>
  requires std::convertible_to<T, float_type>
void generate(T &value) {
  [[maybe_unused]] static auto seed = []() {
    std::srand(std::time(nullptr));
    return 0;
  }();

  value = std::rand() / RAND_COEFF - 1.0f;
};

template <typename T>
  requires std::ranges::range<T> && requires { typename T::value_type; }
void generate(T &container) {
  std::for_each(std::execution::par_unseq, container.begin(), container.end(),
                generate);
};
}; // namespace detail

using detail::generate;

}; // namespace random
}; // namespace ml