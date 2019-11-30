#pragma once

#include <placebo/evil/macro.hpp>
#include <placebo/details/builtin.hpp>

#include <cstddef>
#include <cstdint>

#include <limits>
#include <type_traits>

namespace placebo { namespace details {

template <typename BaseType>
struct warithmetic {
  using unit_t = BaseType;

  static constexpr unit_t unit_max = std::numeric_limits<unit_t>::max();

  template <typename T>
  static constexpr_14 void fill_from_unsigned_builtin(unit_t *begin, unit_t *end, T value) noexcept {
    static_assert(std::is_unsigned<T>::value, "value parameter should be unsigned");

    constexpr auto denominator = sizeof(T) > sizeof(BaseType) ? (static_cast<T>(unit_max) + 1)
                                                              : std::numeric_limits<T>::max();

    for (auto it = begin; it != end; ++it) {
      *it = static_cast<unit_t>(value % denominator);
      value /= denominator;
    }
  }

};

}}

