# ListOperationsKit

### ListOperationsKit is a feature-rich doubly linked list implementation

Built with modern C++ standards, using smart pointers for memory management, providing Python-like list operations.

## Features

- Doubly linked list structure - supports forward and backward operations
- Smart pointer management - automatic memory management, no memory leaks
- STL-style interface - supports range-based for loops and iterators
- Rich operation methods - insert, delete, sort, search, etc.
- Exception safety - proper error handling
- Template support - supports any type
- Stack/Queue implementations - includes companion stack and queue classes

## Included Classes

- `ListOperationsKit<T>` - Main doubly linked list class
- `LinkedStack<T>` - Linked list-based stack implementation
- `LinkedQueue<T>` - Linked list-based queue implementation

## Basic Usage

### Construction and Initialization

```cpp
#include "ListOperationsKit.h"

// Empty list
ListOperationsKit<int> list1;

// Initializer list
ListOperationsKit<int> list2 = {1, 2, 3, 4, 5};

// Copy construction
ListOperationsKit<int> list3(list2);

// Move construction
ListOperationsKit<int> list4 = std::move(list2);
```

### Adding Elements

```cpp
ListOperationsKit<int> list;

// Basic insertion
list.push_back(10);      // Insert at tail
list.push_front(5);      // Insert at head
list.append(20);         // Equivalent to push_back

// Multiple element insertion
list.append(30, 40, 50); // Insert multiple elements at once

// Insert at specific position
list.insert_at(2, 15);   // Insert 15 at index 2

// In-place construction
list.emplace_back(60);   // Construct element at tail
list.emplace_front(0);   // Construct element at head

// Random filling
list.random_append(5);        // Add 5 random numbers (0-100)
list.random_append(3, 1, 10); // Add 3 random numbers (1-10)
```

### Accessing Elements

```cpp
ListOperationsKit<int> list = {10, 20, 30, 40, 50};

// Basic access
int first = list.front();    // Get first element: 10
int last = list.back();      // Get last element: 50

// Index access
int val1 = list[2];          // Get element at index 2: 30
int val2 = list.get(3);      // Get element at index 3: 40
int val3 = list(1);          // Function call syntax: 20

// Modify elements
list[0] = 100;               // Modify element at index 0
list.set(1, 200);            // Modify element at index 1
```

### Removing Elements

```cpp
ListOperationsKit<int> list = {1, 2, 3, 4, 5};

// Basic removal
list.pop_front();            // Remove first element
list.pop_back();             // Remove last element

// Remove by index
list.remove(1);              // Remove element at index 1

// Clear all
list.clear();                // Clear all elements
```

### Iteration

```cpp
ListOperationsKit<int> list = {1, 2, 3, 4, 5};

// Range-based for loop (recommended)
for (const auto& item : list) {
    std::cout << item << " ";
}

// Using iterators
for (auto it = list.begin(); it != list.end(); ++it) {
    std::cout << *it << " ";
}

// Reverse iteration (using indices)
for (int i = static_cast<int>(list.size()) - 1; i >= 0; --i) {
    std::cout << list[i] << " ";
}

// Convenient reverse printing
list.print_reverse();
```

## Advanced Features

### Search and Statistics

```cpp
ListOperationsKit<int> list = {1, 2, 3, 2, 4, 2, 5};

// Find element (exception throwing version)
try {
    size_t pos = list.index(2);      // Find first occurrence of 2
    std::cout << "Found at index: " << pos << std::endl;
} catch (const std::out_of_range& e) {
    std::cout << "Element not found" << std::endl;
}

// Find element (non-throwing version)
size_t pos = list.find_index(99);
if (pos != std::numeric_limits<size_t>::max()) {
    std::cout << "Found at index: " << pos << std::endl;
}

// Check if element exists
bool exists = list.contains(3);     // true

// Count element occurrences
size_t count = list.count(2);       // 3
```

### Sorting and Reversing

```cpp
ListOperationsKit<int> list = {5, 2, 8, 1, 9};

// Sorting
list.sort();                        // Ascending: 1 2 5 8 9
list.sort(true);                    // Descending: 9 8 5 2 1
list.sort(std::greater<int>());     // Using custom comparator

// Reversing
list.reverse();                     // Reverse element order
```

### Slicing and Copying

```cpp
ListOperationsKit<int> list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// Slicing (start index, end index, step)
auto slice1 = list.slice(2, 8);     // {2, 3, 4, 5, 6, 7}
auto slice2 = list.slice(1, 9, 2);  // {1, 3, 5, 7}

// Copying
auto copy = list.copy();

// Swap elements
list.swap(0, 9);                    // Swap elements at indices 0 and 9
```

### List Operations

```cpp
ListOperationsKit<int> list1 = {1, 2, 3};
ListOperationsKit<int> list2 = {4, 5, 6};

// Concatenate lists
list1.concatenate(list2);           // list1 becomes {1, 2, 3, 4, 5, 6}

// Comparison operations
bool equal = (list1 == list2);
bool less = (list1 < list2);
```

## Output and String Conversion

```cpp
ListOperationsKit<int> list = {1, 2, 3, 4, 5};

// Direct output
std::cout << list;                  // Output: 1 2 3 4 5

// Convert to string
std::string str = list.to_string(); // "1 2 3 4 5"

// Print methods
list.print();                       // Print with newline
list.print_reverse();               // Print in reverse with newline
```

## Size and Status

```cpp
ListOperationsKit<int> list = {1, 2, 3};

// Size queries
size_t s1 = list.size();            // 3
size_t s2 = list.get_size();        // 3  
size_t s3 = list.length();          // 3

// Status queries
bool empty = list.empty();          // false
size_t max_size = list.max_size();  // Maximum possible size
```

## Stack and Queue Usage

### LinkedStack Usage

```cpp
LinkedStack<int> stack;

// Basic operations
stack.push(10);
stack.push(20);
stack.push(30);

std::cout << "Top: " << stack.top() << std::endl;  // 30
std::cout << "Size: " << stack.size() << std::endl; // 3

while (!stack.empty()) {
    std::cout << stack.top() << " ";
    stack.pop();
}
```

### LinkedQueue Usage

```cpp
LinkedQueue<int> queue;

// Basic operations
queue.push(10);
queue.push(20);
queue.push(30);

std::cout << "Front: " << queue.front() << std::endl; // 10
std::cout << "Back: " << queue.back() << std::endl;   // 30
std::cout << "Size: " << queue.size() << std::endl;   // 3

while (!queue.empty()) {
    std::cout << queue.front() << " ";
    queue.pop();
}
```

## Complete Example

```cpp
#include "ListOperationsKit.h"
#include <iostream>

int main() {
    // Create and initialize list
    ListOperationsKit<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};
    
    std::cout << "Original list: " << numbers << std::endl;
    
    // Add elements
    numbers.append(8, 7);
    numbers.insert_at(2, 99);
    std::cout << "After adding: " << numbers << std::endl;
    
    // Sort
    numbers.sort();
    std::cout << "After sorting: " << numbers << std::endl;
    
    // Search
    try {
        size_t pos = numbers.index(99);
        std::cout << "99 is at index: " << pos << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "99 not found" << std::endl;
    }
    
    // Count
    std::cout << "1 appears " << numbers.count(1) << " times" << std::endl;
    
    // Slice
    auto subset = numbers.slice(2, 6);
    std::cout << "Subset [2:6]: " << subset << std::endl;
    
    // Reverse
    numbers.reverse();
    std::cout << "After reversing: " << numbers << std::endl;
    
    return 0;
}
```

## Important Notes

1. **Index bounds**: Accessing non-existent indices throws `std::out_of_range` exception
2. **Empty list operations**: Calling `front()`, `back()`, `pop_front()`, `pop_back()` on empty list throws exception
3. **Memory management**: Uses smart pointers, no manual memory management required
4. **Exception safety**: All operations provide basic exception safety guarantees

## Requirements

- C++20 or higher
- Standard library support for smart pointers and STL containers
