#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <placebo/details/arithmetic.hpp>
#include <memory>

class fill_from_unsigned_builtin_test : public testing::Test {
protected:
  using arithmetic16 = placebo::details::warithmetic<uint16_t>;
  using arithmetic32 = placebo::details::warithmetic<uint32_t>;
  using arithmetic64 = placebo::details::warithmetic<uint64_t>;
};

TEST_F(fill_from_unsigned_builtin_test, 16bit) {
  uint16_t arr4[4];
  arithmetic16::fill_from_unsigned_builtin(arr4, arr4 + 4, 150ul);
  ASSERT_THAT(arr4, testing::ElementsAre(150, 0, 0, 0));

  arithmetic16::fill_from_unsigned_builtin(arr4, arr4 + 4, 18446744073709551615ull);
  ASSERT_THAT(arr4, testing::ElementsAre(65535, 65535, 65535, 65535));

  uint16_t arr2[2];
  arithmetic16::fill_from_unsigned_builtin(arr2, arr2 + 2, 4294967296ull); // overflow
  ASSERT_THAT(arr2, testing::ElementsAre(0, 0));
}

TEST_F(fill_from_unsigned_builtin_test, 32bit) {
  uint32_t arr2[2];
  arithmetic32::fill_from_unsigned_builtin(arr2, arr2 + 2, 350ul);
  ASSERT_THAT(arr2, testing::ElementsAre(350, 0));

  arithmetic32::fill_from_unsigned_builtin(arr2, arr2 + 2, 18446744073709551615ull);
  ASSERT_THAT(arr2, testing::ElementsAre(4294967295ul, 4294967295ul));

  uint32_t arr[1];
  arithmetic32::fill_from_unsigned_builtin(arr, arr + 1, 4294967296ull); // overflow
  ASSERT_EQ(arr[0], 0);
}

TEST_F(fill_from_unsigned_builtin_test, 64bit) {
  uint64_t arr[1];
  arithmetic64::fill_from_unsigned_builtin(arr, arr + 1, 100ul);
  ASSERT_EQ(arr[0], 100);
}
