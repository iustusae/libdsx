#include <cassert>
#include <iostream>
// vector_test.cpp
#include "src/vector/vector.hpp"
#include "vector/v_exceptions.hpp"
#include <gtest/gtest.h>
// Test fixture for the vector class
class VectorTest : public ::testing::Test
{
  protected:
    dsx::structs::vector<int> emptyVector;  // Empty vector for testing
    dsx::structs::vector<int> filledVector; // Vector with some initial

    void SetUp() override
    {
        filledVector.push(10);
        filledVector.push(20);
        filledVector.push(30);
    }
};

TEST_F(VectorTest, DefaultConstructor)
{
    EXPECT_EQ(emptyVector.len(), 0);
    EXPECT_EQ(emptyVector.capacity(), 5);
    EXPECT_TRUE(emptyVector.is_empty());
}

TEST_F(VectorTest, InitializerListConstructor)
{
    dsx::structs::vector<int> vectorWithElements = {1, 2, 3};
    EXPECT_EQ(vectorWithElements.len(), 3);
    EXPECT_EQ(vectorWithElements.capacity(), 5);
    EXPECT_FALSE(vectorWithElements.is_empty());

    EXPECT_EQ(vectorWithElements[0], 1);
    EXPECT_EQ(vectorWithElements[1], 2);
    EXPECT_EQ(vectorWithElements[2], 3);
}

TEST_F(VectorTest, SizeConstructor)
{
    dsx::structs::vector<int> sizedVector(10);
    EXPECT_EQ(sizedVector.len(), 0);
    EXPECT_EQ(sizedVector.capacity(), 10);
    EXPECT_TRUE(sizedVector.is_empty());
}

TEST_F(VectorTest, Accessors)
{
    // Test at()
    EXPECT_EQ(filledVector.at(0), 10);
    EXPECT_EQ(filledVector.at(1), 20);
    EXPECT_EQ(filledVector.at(2), 30);

    // Test operator[]
    EXPECT_EQ(filledVector[0], 10);
    EXPECT_EQ(filledVector[1], 20);
    EXPECT_EQ(filledVector[2], 30);

    // Test front() and back()
    EXPECT_EQ(filledVector.front(), 10);
    EXPECT_EQ(filledVector.back(), 30);
}

TEST_F(VectorTest, Reserve)
{
    emptyVector.reserve(10);
    EXPECT_EQ(emptyVector.capacity(), 10);
}

TEST_F(VectorTest, Shrink)
{
    filledVector.pop(); // Remove the last element
    filledVector.shrink();
    EXPECT_EQ(filledVector.capacity(), filledVector.len());
}

TEST_F(VectorTest, PushAndPop)
{
    emptyVector.push(100);
    EXPECT_EQ(emptyVector.len(), 1);
    EXPECT_EQ(emptyVector[0], 100);

    auto poppedElement = filledVector.pop();
    EXPECT_TRUE(poppedElement.has_value());
    EXPECT_EQ(poppedElement.value(), 30);
    EXPECT_EQ(filledVector.len(), 2);
}

TEST_F(VectorTest, InsertAndErase)
{
    filledVector.insert_at(25, 1);
    EXPECT_EQ(filledVector[1], 25);
    EXPECT_EQ(filledVector[2], 20);

    auto erasedElement = filledVector.erase_at(0);
    EXPECT_TRUE(erasedElement.has_value());
    EXPECT_EQ(erasedElement.value(), 10);
    EXPECT_EQ(filledVector.len(), 2);
    EXPECT_EQ(filledVector[0], 25);
}

TEST_F(VectorTest, Clear)
{
    filledVector.clear();
    EXPECT_TRUE(filledVector.is_empty());
}

TEST_F(VectorTest, Resize)
{
    filledVector.resize(2);
    EXPECT_EQ(filledVector.len(), 2);

    filledVector.resize(5);
    EXPECT_EQ(filledVector.len(), 5);
}

TEST_F(VectorTest, Swap)
{
    dsx::structs::vector<int> tempVector = {100, 200};

    filledVector.swap(tempVector);

    EXPECT_EQ(filledVector.len(), 2);
    EXPECT_EQ(tempVector.len(), 3);

    EXPECT_EQ(filledVector[0], 100);
    EXPECT_EQ(tempVector[0], 10);
}

TEST_F(VectorTest, NegativeIndicies)
{
    dsx::structs::vector<std::string> vec = {"ayman", "ahmed", "tarik"};
    EXPECT_THROW(vec[-1], dsx::structs::exceptions::NegativeIndexExecption);
}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// #include "vector/vector.hpp"
// #include <cassert>
// #include <iostream>
// int main() {
//   dsx::structs::vector<int> vec = {1, 2, 4};

//   std::cout << vec.at(-2).value_or(-1);

//   return 0;
// }
