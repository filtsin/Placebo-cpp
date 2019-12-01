#pragma once

#include <placebo/evil/macro.hpp>
#include <placebo/details/traits.hpp>

#include <type_traits>
#include <cstddef>

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

/*
 * Multiplication of two numbers that can give overflow but can't saved in builtin type (uint64_t for example)
 * Save result as 2 numbers with T type as {higher;lower} one number in binary form
 *
 * For example (sizeof(T) = 1),
 *  value1 = 234 (11101010b)
 *  value2 = 189 (10111101b)
 *
 *               1110 1010
 *               1011 1101
 *               ---------
 *               1110 | 1010   <-- mul = 11101010 * 1101
 *              00000 | 000
 *             111010 | 10
 *            1110101 | 0
 *            ------------
 *           10111110 | 0010   <-- It is last 4 bits of result, we know it by taking last 4 bits of the mul
 *           -------------
 *           11101010          <-- mul2 = 11101010 * 1011
 *       1 | 101010
 *      00 | 000000
 *     111 | 01010
 *          --------------
 *    1010 | 11001100 | 0010
 *      ^        ^
 *      |        |
 *      |    It is sum of first 8 bits of the mul and last 8 bits of the mul2
 *      |
 *   It is first 4 bits of the result, we know it by taking last 4 bits of the mul2 and check overflow in sum of
 *   first 8 bits of the mul and last 8 bits of the mul2
 *
 *   Result: top is 10101100, low is 11000010
 *
 */
template <typename T, typename std::enable_if<!has_2x_bits<T>::value>::type* = nullptr>
constexpr_14 number_parts<T> multiplication_of_unsigned_builtin(T val1, T val2) noexcept {
  static_assert(std::is_unsigned<T>::value, "T should be unsigned");

  constexpr size_t t_size  = sizeof(T) * 4; // (sizeof(T) * 8) / 2
  constexpr T      mask    = (static_cast<T>(1) << t_size) - 1;

  const T lower_of_value1  = static_cast<T>(val1 & mask);
  const T higher_of_value1 = static_cast<T>(val1 >> t_size);
  const T lower_of_value2  = static_cast<T>(val2 & mask);
  const T higher_of_value2 = static_cast<T>(val2 >> t_size);

  const T ll  = static_cast<T>(lower_of_value1  * lower_of_value2);
  const T hl  = static_cast<T>(higher_of_value1 * lower_of_value2);
  const T lh  = static_cast<T>(lower_of_value1  * higher_of_value2 + (ll >> t_size) + hl);
  const T hh  = static_cast<T>(higher_of_value1 * higher_of_value2);

  const T low  = static_cast<T>((ll & mask) + (lh << t_size));
  const T top  = static_cast<T>((lh >> t_size) + hh + ((lh < hl) ? (mask + 1) : 0));

  return {top, low};
}



}}

