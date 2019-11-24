#include <gtest/gtest.h>

#include <placebo/wint>

TEST(empty, empty) {
  placebo::wint<64, signed, placebo::details::warithmetic<uint64_t>> w(3);
  ASSERT_EQ(0, 0);
}
