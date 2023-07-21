#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include "vector.hpp" // Include your custom vector header

template<typename T>
double benchmarkCustomVectorPushBack(long long iterations) {
    dsx::structs::vector<T> custom_vector(iterations);


    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        custom_vector.push(i);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    return duration.count() * 1000.0;
}

template<typename T>
double benchmarkStdVectorPushBack(long long iterations) {
    std::vector<T> std_vector;
    std_vector.reserve(iterations);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        std_vector.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    return duration.count() * 1000.0;
}

int vec_bench() {
    std::vector<long long> iters;
    for (int i = 0; i <= 10; i++) {
        iters.push_back(pow(10, i));
    }

    std::cout << "Benchmarking push_back():\n";
    std::cout << "------------------------\n";

    for (long long iteration : iters) {
        std::cout << "Iterations: " << iteration << std::endl;

        // Benchmarking int
        double custom_int_time = benchmarkCustomVectorPushBack<int>(iteration);
        double std_int_time = benchmarkStdVectorPushBack<int>(iteration);

        std::cout << "Custom vector (int) time: " << custom_int_time << " ms\n";
        std::cout << "Std vector (int) time: " << std_int_time << " ms\n";
        std::cout << "Winner: " << ((custom_int_time < std_int_time) ? "Custom Vector" : "Std Vector") << "\n";
        std::cout << "Faster by: " << ((custom_int_time < std_int_time) ?
                                       (std_int_time - custom_int_time) : (custom_int_time - std_int_time)) << " ms\n";
        std::cout << "---------------------------------\n";
    }

    return 0;
}
