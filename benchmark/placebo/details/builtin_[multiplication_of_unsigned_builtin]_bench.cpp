#include <benchmark/benchmark.h>

#include <int_random.hpp>

#include <placebo/details/builtin.hpp>
#include <cstdint>

template <typename T>
void multiplication_of_unsigned_builtin_bench(benchmark::State &state) {
  int_random<T> random;

  for (auto _ : state) {
    placebo::details::multiplication_of_unsigned_builtin(random(), random());
  }
}

BENCHMARK_TEMPLATE(multiplication_of_unsigned_builtin_bench, uint16_t);
BENCHMARK_TEMPLATE(multiplication_of_unsigned_builtin_bench, uint32_t);
BENCHMARK_TEMPLATE(multiplication_of_unsigned_builtin_bench, uint64_t);
