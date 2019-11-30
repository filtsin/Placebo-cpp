#pragma once

#include <placebo/evil/macro.hpp>
#include <placebo/details/traits.hpp>

#include <type_traits>

namespace placebo { namespace details {

// If T has x bits => number_part has 2x bits {top; low} (BE)
template <typename T>
struct number_parts {
  T top;
  T low;
};

template <typename T, typename std::enable_if<has_2x_bits<T>::value>::type* = nullptr>
constexpr_14 number_parts<T> multiplication_of_unsigned_builtin(T val1, T val2) noexcept {
  static_assert(std::is_unsigned<T>::value, "T should be unsigned");

  using res_t = typename unum_2x_bits<T>::type;
  const res_t result = static_cast<res_t>(val1) * static_cast<res_t>(val2);

  const T top = static_cast<T>(result >> (sizeof(T) * 8));
  const T low = static_cast<T>(result);

  return {top, low};
}

template <typename T, typename std::enable_if<!has_2x_bits<T>::value>::type* = nullptr>
constexpr_14 number_parts<T> multiplication_of_unsigned_builtin(T val1, T val2) noexcept {
  static_assert(std::is_unsigned<T>::value, "T should be unsigned");
  // TODO
  unused(val1);
  unused(val2);

  return {0, 0};
}



}}

