cmake_minimum_required(VERSION 3.12)
project(libdsx VERSION 1.0.0)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory to the search path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/src/queue )

# Add the main executable target
add_executable(main main.cxx src/vector/vector.hpp src/vector/vec_test.hpp src/vector/vec_benchmark.hpp src/queue/queue.hpp src/vector/v_exceptions.hpp)
target_compile_options(main PRIVATE -std=c++20 -Wall -Werror)
enable_testing()

    find_package(GTest CONFIG REQUIRED)
    target_link_libraries(main PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
# You can add more executables or tests as needed
# add_executable(another_executable source_files.cpp)
# add_executable(test_my_library test_files.cpp)
