#include <benchmark/benchmark.h>

#include <int_random.hpp>

#include <placebo/details/arithmetic.hpp>
#include <cstdint>
#include <random>
#include <iostream>

template <typename T>
void fill_from_unsigned_builtin_bench(benchmark::State &state) {
  int_random<T> random;

  constexpr auto size = sizeof(uint64_t) / sizeof(T);
  T arr[size];
  for (auto _ : state) {
    placebo::details::warithmetic<T>::fill_from_unsigned_builtin(arr, arr + size, random());
  }
}

BENCHMARK_TEMPLATE(fill_from_unsigned_builtin_bench, uint16_t);
BENCHMARK_TEMPLATE(fill_from_unsigned_builtin_bench, uint32_t);
BENCHMARK_TEMPLATE(fill_from_unsigned_builtin_bench, uint64_t);
