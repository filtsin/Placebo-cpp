#include <benchmark/benchmark.h>

#include <placebo/details/builtin.hpp>
#include <cstdint>
#include <limits>
#include <random>

template <typename T>
class multiplication_of_unsigned_builtin: public benchmark::Fixture {
public:
  multiplication_of_unsigned_builtin() : gen(rd()), distr(0, std::numeric_limits<T>::max()) {}

protected:

  T random() {
    return distr(gen);
  }

  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<T> distr;
};

BENCHMARK_TEMPLATE_F(multiplication_of_unsigned_builtin, 16bit, uint16_t)(benchmark::State &state) {
  uint16_t val1;
  uint16_t val2;
  for (auto _ : state) {
    val1 = random();
    val2 = random();
    placebo::details::multiplication_of_unsigned_builtin(val1, val2);
  }
}

BENCHMARK_TEMPLATE_F(multiplication_of_unsigned_builtin, 32bit, uint32_t)(benchmark::State &state) {
  uint32_t val1;
  uint32_t val2;
  for (auto _ : state) {
    val1 = random();
    val2 = random();
    placebo::details::multiplication_of_unsigned_builtin(val1, val2);
  }
}

BENCHMARK_TEMPLATE_F(multiplication_of_unsigned_builtin, 64bit, uint64_t)(benchmark::State &state) {
  uint64_t val1;
  uint64_t val2;
  for (auto _ : state) {
    val1 = random();
    val2 = random();
    placebo::details::multiplication_of_unsigned_builtin(val1, val2);
  }
}