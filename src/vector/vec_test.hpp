#include <cassert>
#include <iostream>

#include "vector.hpp"

// Helper macro for test assertions
#define ASSERT(condition)                                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(condition))                                                                                              \
        {                                                                                                              \
            std::cerr << "Assertion failed at line " << __LINE__ << " in function " << __FUNCTION__ << ": "            \
                      << #condition << std::endl;                                                                      \
            exit(-1);                                                                                                  \
        }                                                                                                              \
    } while (0)

inline int vec_test()
{
    // Test 1: Default constructor
    dsx::structs::vector<int> v1;
    ASSERT(v1.len() == 0);
    ASSERT(v1.capacity() == 5);
    std::cout << "Test 1 (Default Constructor) passed!" << std::endl;

    // Test 2: Initializer_list constructor
    dsx::structs::vector<int> v2 = {1, 2, 3};
    ASSERT(v2.len() == 3);
    ASSERT(v2.capacity() == 5);
    ASSERT(v2[0] == 1);
    ASSERT(v2[1] == 2);
    ASSERT(v2[2] == 3);
    std::cout << "Test 2 (Initializer_list Constructor) passed!" << std::endl;

    // Test 3: Size constructor
    dsx::structs::vector<int> v3(4);
    ASSERT(v3.len() == 0);
    ASSERT(v3.capacity() == 4);
    std::cout << "Test 3 (Size Constructor) passed!" << std::endl;

    // Test 4: Push and Pop
    v1.push(10);
    v1.push(20);
    v1.push(30);
    ASSERT(v1.len() == 3);
    ASSERT(v1[0] == 10);
    ASSERT(v1[1] == 20);
    ASSERT(v1[2] == 30);
    auto popped = v1.pop();
    ASSERT(popped.has_value());
    ASSERT(popped.value() == 30);
    ASSERT(v1.len() == 2);
    std::cout << "Test 4 (Push and Pop) passed!" << std::endl;

    // Test 5: Insert_at
    dsx::structs::vector<int> v4 = {1, 2, 3};
    v4.insert_at(0, 0);
    v4.insert_at(4, 4);
    ASSERT(v4.len() == 5);
    ASSERT(v4[0] == 0);
    ASSERT(v4[1] == 1);
    ASSERT(v4[2] == 2);
    ASSERT(v4[3] == 3);
    ASSERT(v4[4] == 4);
    std::cout << "Test 5 (Insert_at) passed!" << std::endl;

    // Test 6: Erase_at
    dsx::structs::vector<int> v5 = {1, 2, 3};
    auto erased = v5.erase_at(1);
    ASSERT(erased.has_value() && erased.value() == 2);
    ASSERT(v5.len() == 2);
    ASSERT(v5[0] == 1);
    ASSERT(v5[1] == 3);
    std::cout << "Test 6 (Erase_at) passed!" << std::endl;

    // Test 7: Clear
    dsx::structs::vector<int> v6 = {1, 2, 3};
    v6.clear();
    ASSERT(v6.len() == 0);
    ASSERT(v6.capacity() == 5);
    std::cout << "Test 7 (Clear) passed!" << std::endl;

    // Test 8: Resize
    dsx::structs::vector<int> v7 = {1, 2, 3};
    v7.resize(2);
    ASSERT(v7.len() == 2);
    ASSERT(v7[0] == 1);
    ASSERT(v7[1] == 2);
    std::cout << "Test 8 (Resize) passed!" << std::endl;

    // Test 9: Swap
    dsx::structs::vector<int> v8 = {1, 2, 3};
    dsx::structs::vector<int> v9 = {4, 5, 6, 3};
    v8.swap(v9);
    ASSERT(v8.len() == 4 && v8[0] == 4 && v8[1] == 5 && v8[2] == 6);
    ASSERT(v9.len() == 3 && v9[0] == 1 && v9[1] == 2 && v9[2] == 3);
    std::cout << "Test 9 (Swap) passed!" << std::endl;

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
