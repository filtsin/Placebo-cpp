#pragma once

#include <cstdint>
#include <type_traits>

namespace placebo { namespace details {

template <typename T>
struct has_2x_bits {
  static constexpr bool value =  std::is_integral<T>::value && sizeof(T) != sizeof(uint64_t);
};

// Convert T type with x bits to numeric type (unsigned) with 2x bits
template <typename T, typename U = std::integral_constant<bool, true>>
struct unum_2x_bits {};

template <typename T>
struct unum_2x_bits<T, std::integral_constant<bool, sizeof(T) == sizeof(uint8_t) && std::is_integral<T>::value>> {
  using type = uint16_t;
};

template <typename T>
struct unum_2x_bits<T, std::integral_constant<bool, sizeof(T) == sizeof(uint16_t) && std::is_integral<T>::value>> {
  using type = uint32_t;
};

template <typename T>
struct unum_2x_bits<T, std::integral_constant<bool, sizeof(T) == sizeof(uint32_t) && std::is_integral<T>::value>> {
  using type = uint64_t;
};

}}
