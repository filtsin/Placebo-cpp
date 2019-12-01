#include <gtest/gtest.h>

#include <placebo/details/builtin.hpp>

#include <cstdint>
#include <tuple>
#include <limits>

// Overflow case
template <typename U>
struct overflow_test {};

template <>
struct overflow_test<uint16_t> {
  enum : uint16_t {
    // values:
    val1  = 60000,
    val2  = 50000,
    // result:
    top   = 45776,
    low   = 24064
  };
};

template <>
struct overflow_test<uint32_t> {
  enum : uint32_t {
    // values:
    val1  = 4000000000,
    val2  = 2000000000,
    // result:
    top   = 1862645149,
    low   = 991952896
  };
};

template <>
struct overflow_test<uint64_t> {
  enum : uint64_t {
    // values:
    val1  = 18000000000000000000ull,
    val2  = 10000000000000000000ull,
    // result:
    top   = 9757819552369539906ull,
    low   = 1237319192521211904ull
  };
};

template <typename T>
class multiplication_of_unsigned_builtin_test : public testing::Test {
public:
  void standart_test() {
    T val1 = overflow_test<T>::val1;
    T val2 = overflow_test<T>::val2;
    T top  = overflow_test<T>::top;
    T low  = overflow_test<T>::low;
    auto result = placebo::details::multiplication_of_unsigned_builtin(val1, val2);

    EXPECT_EQ(std::tie(result.top, result.low), std::make_tuple(top, low));

    val1 = 30000;
    val2 = 2;
    result = placebo::details::multiplication_of_unsigned_builtin(val1, val2);
    EXPECT_EQ(std::tie(result.top, result.low), std::make_tuple(0, 60000));

    val1 = 10;
    val2 = 0;
    result = placebo::details::multiplication_of_unsigned_builtin(val1, val2);
    EXPECT_EQ(std::tie(result.top, result.low), std::make_tuple(0, 0));
  }
};

using types = ::testing::Types<uint16_t, uint32_t, uint64_t>;
TYPED_TEST_SUITE(multiplication_of_unsigned_builtin_test, types);

TYPED_TEST(multiplication_of_unsigned_builtin_test, common) {
  this->standart_test();
}
