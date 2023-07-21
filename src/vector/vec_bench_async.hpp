//
// Created by Ayman Ougri on 7/21/23.
//

#ifndef LIBDSX_VEC_BENCH_ASYNC_HPP
#define LIBDSX_VEC_BENCH_ASYNC_HPP
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <future> // Include the <future> header for async
#include "vector.hpp"
// ... (rest of the code remains the same)

// Helper function to run the benchmark and return the time taken
template<typename T>
double benchmarkCustomVectorPushBackHelper(long long iterations) {
    dsx::structs::vector<T> custom_vector(iterations);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        custom_vector.push(i);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    return duration.count() * 1000.0;
}

// Helper function to run the std::vector benchmark and return the time taken
template<typename T>
double benchmarkStdVectorPushBackHelper(long long iterations) {
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

int vec_bench_async() {
    std::vector<long long> iters;
    for (int i = 0; i <= 10; i++) {
        iters.push_back(pow(10, i));
    }

    std::cout << "Benchmarking push_back():\n";
    std::cout << "------------------------\n";

    for (long long iteration : iters) {
        std::cout << "Iterations: " << iteration << std::endl;

        // Launch two threads for concurrent benchmarking
        std::future<double> custom_int_future = std::async(std::launch::async, benchmarkCustomVectorPushBackHelper<int>, iteration);
        std::future<double> std_int_future = std::async(std::launch::async, benchmarkStdVectorPushBackHelper<int>, iteration);

        // Get the results from the threads
        double custom_int_time = custom_int_future.get();
        double std_int_time = std_int_future.get();

        std::cout << "Custom vector (int) time: " << custom_int_time << " ms\n";
        std::cout << "Std vector (int) time: " << std_int_time << " ms\n";
        std::cout << "Winner: " << ((custom_int_time < std_int_time) ? "Custom Vector" : "Std Vector") << "\n";
        std::cout << "Faster by: " << ((custom_int_time < std_int_time) ?
                                       (std_int_time - custom_int_time) : (custom_int_time - std_int_time)) << " ms\n";
        std::cout << "---------------------------------\n";
    }

    return 0;
}

#endif //LIBDSX_VEC_BENCH_ASYNC_HPP
