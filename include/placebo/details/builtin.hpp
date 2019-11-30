#pragma once

#include <placebo/evil/macro.hpp>
#include <placebo/details/traits.hpp>

#include <cstdint>
#include <type_traits>
#include <limits>

namespace placebo { namespace details {

// If T has x bits => number_part has 2x bits {top; low} (BE)
template <typename T>
struct number_parts {
  T top;
  T low;
};

}}

