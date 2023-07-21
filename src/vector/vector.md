# dsx::vector |  Features

### Constructor(s): A constructor is used to initialize the vector object. It may have various forms, such as a default constructor, a constructor with initial size, or a constructor that initializes the vector with given values

### Destructor: A destructor is responsible for releasing any allocated memory and cleaning up resources when the vector object goes out of scope

### Capacity Methods

#### `size()`: Returns the current number of elements in the vector

#### `capacity()`: Returns the current size of the allocated storage (how many elements the vector can hold without reallocating)

#### `empty()`: Checks whether the vector is empty or not

#### `reserve()`: Requests a change in capacity without changing the vector's size

#### `shrink_to_fit()`: Requests the container to reduce its capacity to fit its size

### Element Access Methods

#### `operator[]`: Accesses elements in the vector using the subscript operator

#### `at()`: Accesses elements in the vector with bounds checking, throwing an exception if the index is out of range

#### `front()`: Returns a reference to the first element in the vector

#### `back()`: Returns a reference to the last element in the vector

### Modifiers

#### `push_back()`: Adds an element to the end of the vector

#### `pop_back()`: Removes the last element from the vector

#### `insert()`: Inserts elements at a specific position

#### `erase()`: Removes elements at a specific posaition or within a range

#### `clear()`: Removes all elements from the vector

#### `resize()`: Changes the size of the vector

#### `swap()`: Swaps the contents of two vectors

### Other Useful Methods

#### `begin(), end()`: Return iterators to the beginning and end of the vector

#### `rbegin(), rend()`: Return reverse iterators to the beginning and end of the vector

#### `emplace()`: Constructs an element in-place at the given position

##### These are some common methods you would typically find in a basic vector implementation. More complex vector implementations might include additional methods and features for specialized use cases
