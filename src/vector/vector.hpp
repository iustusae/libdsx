#pragma once
#include "v_exceptions.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>

/**
 * @brief A dynamic array-based vector container implementation.
 *
 * The vector class provides a dynamic array-based container for holding
 * elements of a specified type. It automatically resizes its underlying array
 * to accommodate the elements as they are added or removed.
 *
 * @tparam T The type of elements held in the vector.
 * @tparam cap The initial capacity of the vector. Defaults to 5.
 */
namespace dsx::structs
{
template <typename T> class vector
{
  private:
    int _cap = 5;
    T *_arr = new T[_cap];
    int _len = {0};

  public:
    /**
     * @brief Default constructor for the vector class.
     *
     * This constructor creates an empty vector with the default initial
     * capacity.
     */
    vector() = default;

    /**
     * @brief Constructor that initializes the vector with elements from an
     * initializer list.
     *
     * This constructor creates a vector with the elements provided in the given
     * initializer list. It sets the length of the vector to the number of
     * elements in the initializer list.
     *
     * @param list An initializer list containing elements to be stored in the
     * vector.
     */
    vector(std::initializer_list<T> list) : _len(list.size())
    {
        _arr = new T[_cap]; // Allocate memory for the array
        std::copy(list.begin(), list.end(),
                  _arr); // Copy elements from the initializer list to the array
    }

    /**
     * @brief Constructor that sets the initial size of the vector.
     *
     * This constructor creates a vector with the specified initial size.
     * It allocates memory for the underlying array with the given size and sets
     * the capacity accordingly.
     *
     * @param p_size The initial size of the vector.
     * @throws std::runtime_error If memory allocation fails.
     */
    explicit vector(int p_size)
    {
        T *n_arr = new T[p_size]; // Allocate memory for the new array with the
                                  // given size

        delete[] _arr; // Deallocate memory from the previous array

        _arr = n_arr; // Update the pointer to the newly allocated array

        if (!_arr)
        {
            std::stringstream ss;
            ss << "Memory reallocation failed at line: " << __LINE__ << " in function: " << __FUNCTION__;
            throw std::runtime_error(ss.str()); // Throw an error if memory allocation fails
        }

        _cap = p_size; // Update the capacity of the vector
    }

    /**
     * @brief Destructor for the vector class.
     *
     * This destructor automatically deallocates the memory used by the
     * underlying array when the vector goes out of scope. It ensures that there
     * are no memory leaks and releases the resources held by the vector.
     */
    ~vector()
    {
        delete[] _arr;
    }

  public:
    /**
     * @brief Get the current number of elements in the vector.
     *
     * This function returns the current number of elements present in the
     * vector.
     *
     * @return The number of elements in the vector.
     */
    [[nodiscard]] int len() const
    {
        return _len;
    }

    /**
     * @brief Get the current capacity of the vector.
     *
     * This function returns the current capacity of the vector, which represents
     * the maximum number of elements that can be stored without reallocation.
     *
     * @return The current capacity of the vector.
     */
    [[nodiscard]] int capacity() const
    {
        return _cap;
    }

    /**
     * @brief Check if the vector is empty.
     *
     * This function checks whether the vector is empty, i.e., if it contains no
     * elements.
     *
     * @return True if the vector is empty, false otherwise.
     */
    [[nodiscard]] bool is_empty() const
    {
        return len() == 0;
    }

    void reserve(int n_size);
    void shrink();

  public:
    /**
     * @brief Returns the element at the specified index.
     *
     * This function provides access to the element at the specified index in the
     * vector. It performs boundary checks to ensure that the index is within the
     * valid range of the vector. If the index is out of range, the function
     * throws an std::out_of_range exception.
     *
     * @param p_idx The index of the element to access.
     * @return The element at the specified index.
     * @throws std::out_of_range If the index is out of range.
     */
    T at(int p_idx) const
    {
        if (p_idx < 0)
        {
            throw dsx::structs::exceptions::NegativeIndexExecption();
        }

        if (p_idx >= _len)
        {
            throw std::out_of_range("The index: " + std::to_string(p_idx) + " is out of bounds of vector with len " +
                                    std::to_string(this->_len));
        }
        return _arr[p_idx]; // Access the element at the specified index
    }

    /**
     * @brief Returns a reference to the element at the specified index.
     *
     * This operator provides direct access to the element at the specified index
     * in the vector. It performs boundary checks to ensure that the index is
     * within the valid range of the vector. If the index is out of range, the
     * operator throws an std::out_of_range exception.
     *
     * @param idx The index of the element to access.
     * @return A reference to the element at the specified index.
     * @throws std::out_of_range If the index is out of range.
     */
    T &operator[](int p_idx) const noexcept(false)
    {
        if (p_idx < 0)
        {
            throw dsx::structs::exceptions::NegativeIndexExecption();
        }

        if (p_idx >= _len)
        {
            throw std::out_of_range("The index: " + std::to_string(p_idx) + " is out of bounds of vector with len " +
                                    std::to_string(this->_len));
        }
        return _arr[p_idx]; // Access the element at the specified index
    }

    /**
     * @brief Returns a reference to the first element in the vector.
     *
     * This function provides access to the first element in the vector.
     * It is used to retrieve the first element when the vector is not empty.
     * It does not check if the vector is empty; calling this function on an
     * empty vector results in undefined behavior.
     *
     * @return A reference to the first element in the vector.
     */
    const T &front() const noexcept
    {
        return _arr[0]; // Access the first element in the vector
    }

    /**
     * @brief Returns a reference to the last element in the vector.
     *
     * This function provides access to the last element in the vector.
     * It is used to retrieve the last element when the vector is not empty.
     * It does not check if the vector is empty; calling this function on an
     * empty vector results in undefined behavior.
     *
     * @return A reference to the last element in the vector.
     */
    const T &back() const noexcept
    {
        return _arr[_len - 1]; // Access the last element in the vector
    }

  public:
    void push(const T &elt);
    std::optional<T> pop();
    void insert_at(const T &elt, int idx);
    std::optional<T> erase_at(int idx);
    void clear();
    void resize(int n_size);
    void swap(vector<T> &o_vec);
};

} // namespace dsx::structs

/**
 * @brief Reserves memory for a given number of elements in the vector.
 *
 * If the requested size is less than or equal to the current capacity, the
 * function does nothing. Otherwise, it allocates memory for the specified
 * number of elements and copies the existing elements to the newly allocated
 * memory. The function updates the capacity of the vector accordingly.
 *
 * @param n_size The number of elements to reserve memory for.
 * @throws std::runtime_error If memory allocation fails.
 */
template <typename T> void dsx::structs::vector<T>::reserve(int n_size) noexcept(false)
{
    if (n_size <= _cap)
    {
        return; // Do nothing if the requested size is less than or equal to the
                // current capacity
    }

    T *new_arr = new T[n_size]; // Allocate memory for the new array with the given size
    if (!new_arr)
    {
        delete[] new_arr; // Deallocate the memory if allocation fails
        std::stringstream ss;
        ss << "Memory reallocation failed at line: " << __LINE__ << " in function: " << __FUNCTION__;
        throw std::runtime_error(ss.str()); // Throw an error if memory allocation fails
    }

    std::copy(_arr, _arr + _len,
              new_arr); // Copy existing elements to the new array
    delete[] _arr;      // Deallocate the memory used by the previous array
    _arr = new_arr;     // Update the pointer to the newly allocated array
    _cap = n_size;      // Update the capacity of the vector
}

/**
 * @brief Reduces the vector's capacity to fit its size.
 *
 * This function deallocates the unused memory from the underlying array,
 * reducing the vector's capacity to be equal to the number of elements it
 * contains. If the vector is empty, the function does nothing.
 *
 * @throws std::runtime_error If memory reallocation fails while shrinking.
 */
template <typename T> void dsx::structs::vector<T>::shrink() noexcept(false)
{
    if (_len == 0)
    {
        return; // Do nothing if the vector is empty
    }

    T *new_arr = new T[_len];
    if (!new_arr)
    {
        delete[] new_arr; // Deallocate the memory if allocation fails
        std::stringstream ss;
        ss << "Memory reallocation failed at line: " << __LINE__ << " in function: " << __FUNCTION__;
        throw std::runtime_error(ss.str()); // Throw an error if memory allocation fails
    }                                       // Allocate memory for the new array with the size of the vector's length
    std::copy(_arr, _arr + _len, new_arr);  // Copy elements to the new array

    delete[] _arr;  // Deallocate the memory used by the previous array
    _arr = new_arr; // Update the pointer to the newly allocated array
    if (!_arr)
    {
        delete[] new_arr; // Deallocate the memory if allocation fails
        std::stringstream ss;
        ss << "Memory reallocation failed at line: " << __LINE__ << " in function: " << __FUNCTION__;
        throw std::runtime_error(ss.str()); // Throw an error if memory allocation fails
    }

    _cap = _len; // Update the capacity to be equal to the number of elements in
                 // the vector
}
/**
 * @brief Adds an element to the end of the vector.
 *
 * This function adds a new element to the end of the vector.
 * If the vector's size is about to exceed its current capacity, the function
 * doubles the capacity and reallocates memory for the underlying array to
 * accommodate the new element efficiently.
 *
 * @param elt The element to be added to the end of the vector.
 */
template <typename T> void dsx::structs::vector<T>::push(const T &elt)
{
    if (_len + 1 >= _cap)
    {
        reserve(_cap * 2 * sizeof(*_arr)); // Double the capacity if the size is
                                           // about to exceed the current capacity
        _cap *= 2;
    }

    _arr[_len] = elt; // Add the new element to the end of the vector
    _len++;           // Increment the length of the vector
}

/**
 * @brief Removes and returns the last element of the vector.
 *
 * This function removes the last element of the vector and returns it as an
 * optional value. If the vector is empty, the function returns an empty
 * optional (std::nullopt).
 *
 * @return An optional containing the last element of the vector if the vector
 * is not empty, or an empty optional if the vector is empty.
 */
template <typename T> std::optional<T> dsx::structs::vector<T>::pop()
{
    if (is_empty())
    {
        return std::nullopt;
    }

    auto popped = _arr[_len - 1];
    _arr[_len - 1] = {};
    --_len;

    return popped;
}

/**
 * @brief Inserts an element at the specified index.
 *
 * This function inserts a new element at the specified index in the vector.
 * If the index is greater than or equal to the current length of the vector,
 * the function behaves like `push` and adds the element to the end of the
 * vector. If the vector's size is about to exceed its current capacity, the
 * function doubles the capacity and reallocates memory for the underlying
 * array to accommodate the new element efficiently.
 *
 * @param elt The element to be inserted into the vector.
 * @param idx The index at which the element should be inserted.
 */
template <typename T> void dsx::structs::vector<T>::insert_at(const T &elt, int idx) noexcept(false)
{
    if (idx >= _len)
    {
        push(elt); // Behave like push if the index is greater than or equal to
                   // the current length of the vector
    }
    else
    {
        if (_len == _cap)
        {
            // Double the capacity if the size is about to exceed the current
            // capacity
            _cap = (_cap == 0) ? 5 : _cap * 2;
            T *new_arr = new T[_cap];

            std::copy(_arr, _arr + idx,
                      new_arr); // Copy elements before the insertion point
            new_arr[idx] = elt; // Insert the new element at the specified index
            std::copy(_arr + idx, _arr + _len,
                      new_arr + idx + 1); // Copy remaining elements

            delete[] _arr;  // Deallocate the memory used by the previous array
            _arr = new_arr; // Update the pointer to the newly allocated array

            if (!_arr)
            {
                std::stringstream ss;
                ss << "Memory reallocation failed at line: " << __LINE__ << " in function: " << __FUNCTION__;
                throw std::runtime_error(ss.str()); // Throw an error if memory allocation fails
            }

            _len++; // Increment the length of the vector
        }
        else
        {
            for (int i = _len; i > idx; --i)
            {
                _arr[i] = _arr[i - 1]; // Shift elements to make space for the
                                       // new element
            }

            _arr[idx] = elt; // Insert the new element at the specified index

            _len++; // Increment the length of the vector
        }
    }
}

/**
 * @brief Removes and returns the element at the specified index.
 *
 * This function removes the element at the specified index in the vector and
 * returns it as an optional value. If the index is out of range, the function
 * returns an empty optional (std::nullopt).
 *
 * @param idx The index of the element to be removed.
 * @return An optional containing the removed element if the index is valid, or
 * an empty optional if the index is out of range.
 */
template <typename T> std::optional<T> dsx::structs::vector<T>::erase_at(int idx)
{
    if (idx >= _len)
    {
        return std::nullopt; // Return an empty optional if the index is out of
                             // range
    }

    T erased_value = _arr[idx]; // Store the value to be returned
    std::copy(_arr + idx + 1, _arr + _len,
              _arr + idx); // Shift elements to remove the element at the
                           // specified index

    _len--; // Decrement the length of the vector

    return erased_value; // Return the removed element
}

/**
 * @brief Removes all elements from the vector.
 *
 * This function removes all elements from the vector, leaving it empty.
 * It deallocates the memory used by the underlying array and resets the length
 * and capacity to zero.
 *
 * @throws std::runtime_error If memory reallocation fails while clearing the
 * vector.
 */
template <typename T> void dsx::structs::vector<T>::clear() noexcept(false)
{
    T *n_arr = new T[_cap]; // Allocate memory for a new array with the initial
                            // capacity
    delete[] _arr;          // Deallocate the memory used by the previous array
    _arr = n_arr;           // Update the pointer to the newly allocated array

    if (!_arr)
    {
        std::stringstream ss;
        ss << "Memory reallocation failed at line: " << __LINE__ << " in function: " << __FUNCTION__;
        throw std::runtime_error(ss.str()); // Throw an error if memory reallocation fails
    }

    this->_cap = _cap; // Reset the capacity to the initial value
    this->_len = 0;    // Reset the length to zero, effectively clearing the vector
}

/**
 * @brief Resizes the vector to the specified size.
 *
 * This function resizes the vector to the specified size. If the new size is
 * smaller than the current length, elements at the end of the vector are
 * removed. If the new size is larger than the current length, the vector's
 * capacity is adjusted to accommodate the new size efficiently.
 *
 * @param n_size The new size of the vector.
 * @throws std::runtime_error If memory reallocation fails while resizing the
 * vector.
 */
template <typename T> void dsx::structs::vector<T>::resize(int n_size)
{
    if (n_size < _len)
    {
        _len = n_size; // Reduce the vector's length if the new size is smaller
                       // than the current length
    }
    else if (n_size > _len && n_size > _cap)
    {
        reserve(n_size); // Increase the vector's capacity if the new size is
                         // larger than the current capacity
    }

    if (!_arr)
    {
        std::stringstream ss;
        ss << "Memory reallocation failed at line: " << __LINE__ << " in function: " << __FUNCTION__;
        throw std::runtime_error(ss.str()); // Throw an error if memory reallocation fails
    }
}

/**
 * @brief Swaps the contents of two vectors.
 *
 * This function swaps the contents of the current vector with the contents of
 * another vector. It exchanges the lengths, capacities, and underlying arrays
 * of the two vectors.
 *
 * @param o_vec The reference to the vector to be swapped with the current
 * vector.
 */
template <typename T> void dsx::structs::vector<T>::swap(dsx::structs::vector<T> &o_vec)
{
    std::swap(this->_len, o_vec._len); // Swap the lengths
    std::swap(this->_arr,
              o_vec._arr);             // Swap the pointers to the underlying arrays
    std::swap(this->_cap, o_vec._cap); // Swap the capacities
}
