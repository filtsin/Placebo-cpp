#include <benchmark/benchmark.h>

#include <placebo/details/arithmetic.hpp>
#include <cstdint>
#include <limits>
#include <random>

template <typename T, typename U>
class fill_from_unsigned_builtin_bench : public benchmark::Fixture {
public:
  fill_from_unsigned_builtin_bench() : gen(rd()), distr(0, std::numeric_limits<U>::max()) {}

protected:
  using arithmetic = placebo::details::warithmetic<T>;

  U random() {
    return distr(gen);
  }

  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<U> distr;
};

BENCHMARK_TEMPLATE_F(fill_from_unsigned_builtin_bench, 16bit, uint16_t, uint64_t)(benchmark::State &state) {
  uint16_t arr[4];
  for (auto _ : state) {
    arithmetic::fill_from_unsigned_builtin(arr, arr + 4, random());
  }
}

BENCHMARK_TEMPLATE_F(fill_from_unsigned_builtin_bench, 32bit, uint32_t, uint64_t)(benchmark::State &state) {
  uint32_t arr[2];
  for (auto _ : state) {
    arithmetic::fill_from_unsigned_builtin(arr, arr + 2, random());
  }
}

BENCHMARK_TEMPLATE_F(fill_from_unsigned_builtin_bench, 64bit, uint64_t, uint64_t)(benchmark::State &state) {
  uint64_t arr[1];
  for (auto _ : state) {
    arithmetic::fill_from_unsigned_builtin(arr, arr + 1, random());
  }
}

