# ListOperationsKit
### ListOperationsKit is a simple implementation of single linked list
- How to use
```cpp
ListOperationsKit<int> list_1, list_2, list_3, list_4;

// How to add elements
  // int length, int min = 0, int max = 100
  list_1.random_append(10);
  list_2.random_append(10, 2, 50);

  // initialization
  list_3.append(99, 53, 21, 8, 9, 10, 11, 12, 65, 94);
  list_4 = {0, 654, 565, 2632, 2156, 2, 96, 526, 2223, 55}

  std::cout << list_1 << list_2 << list_3 << list_4;

// Load 
list_1[1] = list_2[2]
```
