#pragma once

#include <type_traits>

#include "types.h"

#define ifnt(c) if (!(c))

namespace ml {
namespace utils {
namespace detail {

using namespace types;

template <typename T>
struct default_value {
  static constexpr typename std::decay_t<T> value = std::decay_t<T>{};
};

template <typename T>
using default_value_v = typename default_value<T>::value;

}  // namespace detail

using detail::default_value, detail::default_value_v;

}  // namespace utils

}  // namespace ml