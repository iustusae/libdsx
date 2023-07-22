#include <iostream>
#include "vector/vec_benchmark.hpp"

int main() {
  std::cout << "STARTING VEC_TEST" << std::endl;
  //vec_test();
  //vec_bench();

  dsx::structs::vector<int> vec = {1, 2, 3, 4};
  for(int i = 0; i < vec.len(); i++)
  {
      std::cout << vec[i] << std::endl;
  };

    vec.is_empty();
  return 0;
}