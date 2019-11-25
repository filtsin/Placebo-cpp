#pragma once

#include <placebo/details/arithmetic.hpp>
#include <placebo/evil/macro.hpp>

#include <cstddef>
#include <cstdint>

#include <iostream>

#include <type_traits>

namespace placebo {

template <size_t Bits, typename Sign, typename Arithmetic = details::warithmetic<uint64_t>>
class wint {
public:
  // TODO: May be init with 0 in default constructor?
  constexpr_14 wint() noexcept = default;

  template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  constexpr_14 wint(T rhs) { // I think that explicit here is bad solution now. implicit cast will be nice for this type?
    unused(rhs);
  }


  ~wint() {
    // Base type should be unsigned because we need correct overflow
    static_assert(std::is_unsigned<typename Arithmetic::unit_t>::value, "Base type should be unsigned");
    static_assert(Bits % (unit_sizeof_bits) == 0, ""); // TODO: Add message after
    static_assert(unit_size > 0, ""); // TODO: Add message after. May be remove this assert
  }

private:

  using unit_t = typename Arithmetic::unit_t;
  static constexpr size_t unit_sizeof_bits = sizeof(unit_t) * 8;
  static constexpr size_t unit_size = Bits / unit_sizeof_bits;
  static constexpr bool is_signed = std::is_signed<Sign>::value;

  typename Arithmetic::unit_t data[unit_size];

  // Now I want to save sign in first bit of last unit
  // 1 - negative, 0 - positive
  // For example
  //  value = -34 (Bits = 8) -> data[0] = 10100010
  //  value = 34  (Bits = 8) -> data[0] = 00100010
  // I think that it is good choose because it saves memory
  // Now I don't even see any reason why it is bad
  // TODO: Check next arithmetic for support of this solution


};

}
