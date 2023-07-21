#include <algorithm>
#include <array>
#include <cstddef>
#include <initializer_list>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>
#pragma once

namespace dsx {
namespace structs {
template <typename T, size_t cap = 5> class vector {
private:
  T *_arr = new T[cap];

  size_t _cap = cap;
  size_t _len = {0};

public:
  vector() = default;
  vector(std::initializer_list<T> list) : _len(list.size()) {
    _arr = new T[_cap];
    std::copy(list.begin(), list.end(), _arr);
  }
  vector(size_t p_size) {
      T *n_arr = new T[p_size];

      delete[] _arr;

      _arr = n_arr;

      if (!_arr) {
          std::stringstream ss;
          ss << "Memory reallocation failed at line: " << __LINE__
             << " in function: " << __FUNCTION__;
          throw std::runtime_error(ss.str());
      }

      _cap = p_size;
  };

  ~vector() { delete[] _arr; }

public:
  size_t len() const { return _len; }
  size_t capacity() const { return _cap; }
  bool is_empty() const { return len() == 0; }
  void reserve(size_t n_size);
  void shrink();

public:
  T at(size_t p_idx) const {
    if (p_idx >= _len) {
      throw std::out_of_range("The index: " + std::to_string(p_idx) +
                              " is out of bounds of vector with len " +
                              std::to_string(this->_len));
    }
    if (p_idx < 0) {
      return _arr[_len + p_idx + 1];
    }

    return _arr[p_idx];
  }

  T &operator[](int idx) const {
    if (idx >= _len) {
      throw std::out_of_range("The index: " + std::to_string(idx) +
                              " is out of bounds.");
    }
    if (idx < 0) {
      return _arr[_len + idx + 1];
    }
    return _arr[idx];
  }

  T &front() const { return _arr[0]; }

  T &back() const { return _arr[_len]; }

public:
  void push(const T &elt);
  std::optional<T> pop();
  void insert_at(const T &elt, size_t idx);
  std::optional<T> erase_at(size_t idx);
  void clear();
  void resize(size_t n_size);
  void swap(vector<T, cap> &o_vec);
};

} // namespace structs

} // namespace dsx

template <typename T, size_t cap>
void dsx::structs::vector<T, cap>::reserve(size_t n_size) {
    if (n_size <= _cap) {
        return;
    }

    T* new_arr = new T[n_size];
    if (!new_arr) {
        delete [] new_arr;
        std::stringstream ss;
        ss << "Memory reallocation failed at line: " << __LINE__
           << " in function: " << __FUNCTION__;
        throw std::runtime_error(ss.str());

    }

    std::copy(_arr, _arr + _len, new_arr);
    _cap = n_size;
    delete [] new_arr;
}

template <typename T, size_t cap> void dsx::structs::vector<T, cap>::shrink() {
  if (_len == 0) {
    return;
  }

  T *new_arr = new T[_len];
  std::copy(_arr, _arr + _len, new_arr);
  delete[] _arr;
  _arr = new_arr;
  if (!_arr) {
    throw std::runtime_error(
        "Memory reallocation failed at line: " + std::to_string(__LINE__) +
        " in function: " + std::to_string(__FUNCTION__));
  }
  _cap = _len;
}

template <typename T, size_t cap>
void dsx::structs::vector<T, cap>::push(const T &elt) {
  if (_len + 1 >= _cap) {
    reserve(_cap * 2 * sizeof(*_arr));
    _cap *= 2;
  }

  _arr[_len] = elt;

  _len++;
}

template <typename T, size_t cap>
std::optional<T> dsx::structs::vector<T, cap>::pop() {
  if (is_empty()) {
    return std::nullopt;
  }
  auto popped = _arr[_len - 1];
  std::cout << popped;
  std::copy(_arr + 0,    // copy everything starting here
            _arr + _len, // and ending here, not including it,
            _arr + 0);
  --_len;
  return popped;
}

template <typename T, size_t cap>
void dsx::structs::vector<T, cap>::insert_at(const T &elt, size_t idx) {

  if (idx >= _len) {
    push(elt);
  } else {
    if (_len == _cap) {

      _cap = (_cap == 0) ? 5 : _cap * 2;
      T *new_arr = new T[_cap];

      std::copy(_arr, _arr + idx, new_arr);

      new_arr[idx] = elt;

      std::copy(_arr + idx, _arr + _len, new_arr + idx + 1);

      delete[] _arr;
      _arr = new_arr;

      if (!_arr) {
        std::stringstream ss;
        ss << "Memory reallocation failed at line: " << __LINE__
           << " in function: " << __FUNCTION__;
        throw std::runtime_error(ss.str());
      }

      _len++;
    } else {

      for (size_t i = _len; i > idx; --i) {
        _arr[i] = _arr[i - 1];
      }

      _arr[idx] = elt;

      _len++;
    }
  }
}

template <typename T, size_t cap>
std::optional<T> dsx::structs::vector<T, cap>::erase_at(size_t idx) {
  if (idx >= _len) {
    return std::nullopt;
  }

  T erased_value = _arr[idx];
  std::copy(_arr + idx + 1, _arr + _len, _arr + idx);
  _len--;
  return erased_value;
}

template <typename T, size_t cap> void dsx::structs::vector<T, cap>::clear() {
  T *n_arr = new T[_cap];
  delete[] _arr;
  _arr = n_arr;

  if (!_arr) {
    std::stringstream ss;
    ss << "Memory reallocation failed at line: " << __LINE__
       << " in function: " << __FUNCTION__;
    throw std::runtime_error(ss.str());
  }

  this->_cap = _cap;
  this->_len = 0;
}

template <typename T, size_t cap>
void dsx::structs::vector<T, cap>::resize(size_t n_size) {
  if (n_size < _len) {
    _len = n_size;
  } else if (n_size > _len && n_size > _cap) {
    reserve(n_size);
  }

  if (!_arr) {
    std::stringstream ss;
    ss << "Memory reallocation failed at line: " << __LINE__
       << " in function: " << __FUNCTION__;
    throw std::runtime_error(ss.str());
  }
}

template <typename T, size_t cap>
void dsx::structs::vector<T, cap>::swap(dsx::structs::vector<T, cap> &o_vec) {
  std::swap(this->_len, o_vec._len);
  std::swap(this->_arr, o_vec._arr);
  std::swap(this->_cap, o_vec._cap);
}