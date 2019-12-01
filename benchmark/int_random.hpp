#pragma once

#include <random>

template <typename T>
class int_random {
public:
  int_random() : gen(rd()) {}
  T operator()() {
    return distr(gen);
  }
private:
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<T> distr;
};
