#pragma once

#include <placebo/evil/macro.hpp>

#include <cstddef>
#include <cstdint>

#include <limits>
#include <type_traits>

namespace placebo { namespace details {

template<typename BaseType>
struct warithmetic {
  using unit_t = BaseType;

  static constexpr unit_t unit_max = std::numeric_limits<unit_t>::max();

  template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  constexpr_14 void fill_from_builtin(unit_t *begin, unit_t *end, T value) {
    unused(begin);
    unused(end);
    unused(value);
  }

};

}}

