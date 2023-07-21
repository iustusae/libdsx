#include "vector/vec_test.hpp"
#include <iostream>
#include "vector/vec_benchmark.hpp"
#include "vector/vec_bench_async.hpp"

int main() {
  std::cout << "STARTING VEC_TEST" << std::endl;
  vec_test();
  vec_bench();
  //for the lols
  vec_bench_async();
  return 0;
}