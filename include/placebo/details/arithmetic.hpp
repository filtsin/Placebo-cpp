#pragma once

#include <placebo/evil/macro.hpp>

#include <cstddef>
#include <cstdint>

#include <limits>
#include <type_traits>

namespace placebo { namespace details {


// May be need Sign parameter in template
// Because:
//  1) Easy logic for next functions (?)
//  2) unit_max is different for sign and unsigned

// -> I want take warithmetic for auto_int (with dynamic allocations)
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

