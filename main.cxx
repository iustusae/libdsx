#include <iostream>
#include "vector/vec_benchmark.hpp"
#include "vector/vec_test.hpp"

int main() {
    std::cout << "STARTING VEC_TEST" << std::endl;
    vec_test();
    vec_bench();

    return 0;
}