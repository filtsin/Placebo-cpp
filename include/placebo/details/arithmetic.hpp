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
    static_assert(std::is_unsigned<T>::value, "T should be unsigned");

    constexpr T denominator = sizeof(T) > sizeof(BaseType) ? (static_cast<T>(unit_max) + 1)
                                                           : std::numeric_limits<T>::max();

    for (auto it = begin; it != end; ++it) {
      *it = static_cast<unit_t>(value % denominator);
      value /= denominator;
    }
  }

  static constexpr_14 void fill_from_cpchar(unit_t *begin, unit_t *end, const char *p1, const char *p2) noexcept {
    // TODO: Think about correct strategy. Here is 3 strategies:
      // 1 - 1st incorrect symbol => cancel all
      // 2 - 1st incorrect symbol => stop next work (Now)
      // 3 - skip incorrect symbols
    unused(begin);
    unused(end);
    unused(p1);
    unused(p2);
  }

private:

  static constexpr_14 unit_t add_unit(unit_t *begin, unit_t *end, unit_t value) noexcept {
    unit_t remainder = value;

    for (auto it(begin); it != end && remainder; ++it) {
      *it += remainder;
      remainder = static_cast<unit_t>(*it < remainder);
    }

    return remainder;
  }
};

}}

