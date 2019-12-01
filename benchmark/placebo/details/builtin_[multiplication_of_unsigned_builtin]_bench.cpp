#include <benchmark/benchmark.h>

#include <int_random.hpp>

#include <placebo/details/builtin.hpp>
#include <cstdint>
#include <random>

template <typename T>
void multiplication_of_unsigned_builtin_bench(benchmark::State &state) {
  int_random<T> random;

  T val1;
  T val2;
  for (auto _ : state) {
    val1 = random();
    val2 = random();
    placebo::details::multiplication_of_unsigned_builtin(val1, val2);
  }
}

BENCHMARK_TEMPLATE(multiplication_of_unsigned_builtin_bench, uint16_t);
BENCHMARK_TEMPLATE(multiplication_of_unsigned_builtin_bench, uint32_t);
BENCHMARK_TEMPLATE(multiplication_of_unsigned_builtin_bench, uint64_t);