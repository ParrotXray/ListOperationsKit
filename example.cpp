#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

#include "ListOperationsKit.h"

// Test helper functions
template<typename T>
void print_test_result(const std::string& test_name, const ListOperationsKit<T>& list, const std::string& expected = "") {
    std::cout << "Test " << test_name << ": ";
    std::cout << list;
    if (!expected.empty()) {
        std::cout << "  (Expected: " << expected << ")";
    }
    std::cout << " [Size: " << list.size() << "]\n";
}

void separator(const std::string& title) {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "  " << title << "\n";
    std::cout << std::string(50, '=') << "\n";
}

int main() {
    std::cout << "Modern C++ ListOperationsKit Comprehensive Test\n";
    
    try {
        separator("1. Basic Construction and Insertion Tests");
        
        // Default constructor
        ListOperationsKit<int> list1;
        std::cout << "Default constructor: " << (list1.empty() ? "Empty list" : "Error") << "\n";
        
        // Initializer list constructor
        ListOperationsKit<int> list2 = {1, 2, 3, 4, 5};
        print_test_result("Initializer list construction", list2, "1 2 3 4 5");
        
        // Copy constructor
        ListOperationsKit<int> list3(list2);
        print_test_result("Copy constructor", list3, "1 2 3 4 5");
        
        // Move constructor
        ListOperationsKit<int> temp = {10, 20, 30};
        ListOperationsKit<int> list4 = std::move(temp);
        print_test_result("Move constructor", list4, "10 20 30");
        std::cout << "Original object empty after move: " << (temp.empty() ? "Yes" : "No") << "\n";
        
        separator("2. Insertion Operation Tests");
        
        ListOperationsKit<int> list5;
        
        // push_back test
        list5.push_back(100);
        list5.push_back(200);
        print_test_result("push_back", list5, "100 200");
        
        // push_front test
        list5.push_front(50);
        print_test_result("push_front", list5, "50 100 200");
        
        // append single element
        list5.append(300);
        print_test_result("append single", list5, "50 100 200 300");
        
        // append multiple elements
        list5.append(400, 500, 600);
        print_test_result("append multiple", list5, "50 100 200 300 400 500 600");
        
        // emplace_back test
        list5.emplace_back(700);
        print_test_result("emplace_back", list5, "50 100 200 300 400 500 600 700");
        
        // insert_at test
        list5.insert_at(2, 150);
        print_test_result("insert_at(2, 150)", list5, "50 100 150 200 300 400 500 600 700");
        
        separator("3. Access and Modification Tests");
        
        // Element access
        std::cout << "front(): " << list5.front() << " (Expected: 50)\n";
        std::cout << "back(): " << list5.back() << " (Expected: 700)\n";
        std::cout << "list5[3]: " << list5[3] << " (Expected: 200)\n";
        std::cout << "list5(4): " << list5(4) << " (Expected: 300)\n";
        std::cout << "get(5): " << list5.get(5) << " (Expected: 400)\n";
        
        // Modify elements
        list5[0] = 99;
        list5.set(1, 199);
        print_test_result("After modification", list5, "99 199 150 200 300 400 500 600 700");
        
        // Swap elements
        list5.swap(0, 8);
        print_test_result("swap(0, 8)", list5, "700 199 150 200 300 400 500 600 99");
        
        separator("4. Deletion Operation Tests");
        
        ListOperationsKit<int> list6 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        print_test_result("Initial deletion test", list6);
        
        // pop_front
        list6.pop_front();
        print_test_result("pop_front", list6, "2 3 4 5 6 7 8 9 10");
        
        // pop_back
        list6.pop_back();
        print_test_result("pop_back", list6, "2 3 4 5 6 7 8 9");
        
        // remove by index
        list6.remove(2);
        print_test_result("remove(2)", list6, "2 3 5 6 7 8 9");
        
        // remove by index (replacing original erase iterator)
        list6.remove(3);  // Remove element at index 3
        print_test_result("remove(3)", list6, "2 3 5 7 8 9");
        
        separator("5. Iterator Tests");
        
        ListOperationsKit<int> list7 = {10, 20, 30, 40, 50};
        
        // Forward iteration
        std::cout << "Forward iteration: ";
        for (auto it = list7.begin(); it != list7.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";
        
        // Range-based for loop
        std::cout << "Range-based for: ";
        for (const auto& val : list7) {
            std::cout << val << " ";
        }
        std::cout << "\n";
        
        separator("6. Sorting Tests");
        
        ListOperationsKit<int> list8 = {5, 2, 8, 1, 9, 3};
        print_test_result("Before sorting", list8);
        
        list8.sort();
        print_test_result("Member function sort", list8, "1 2 3 5 8 9");
        
        list8.sort(true);  // Descending
        print_test_result("Member function sort descending", list8, "9 8 5 3 2 1");
        
        // Using our custom find method
        try {
            size_t found_index = list8.index(5);
            std::cout << "Custom find(5): Found at index " << found_index << "\n";
        } catch (const std::out_of_range& e) {
            std::cout << "Custom find(5): Not found\n";
        }
        
        // Using our custom count method
        list8.append(5, 5, 5);
        int count = list8.count(5);
        std::cout << "Custom count(5): " << count << " occurrences\n";
        
        separator("7. Utility Function Tests");
        
        ListOperationsKit<int> list9 = {1, 2, 3, 2, 4, 2, 5};
        print_test_result("Utility function test", list9);
        
        // count and index
        std::cout << "count(2): " << list9.count(2) << " occurrences\n";
        try {
            std::cout << "index(4): " << list9.index(4) << " (index)\n";
        } catch (const std::out_of_range& e) {
            std::cout << "index(4): Not found\n";
        }
        
        // Test index with non-existent element
        try {
            size_t not_found = list9.index(99);
            std::cout << "index(99): " << not_found << "\n";
        } catch (const std::out_of_range& e) {
            std::cout << "index(99): Not found (exception thrown)\n";
        }
        
        // slice
        auto sliced = list9.slice(1, 5, 2);  // From index 1 to 5, step 2
        print_test_result("slice(1, 5, 2)", sliced, "2 2");
        
        // copy
        auto copied = list9.copy();
        print_test_result("copy", copied);
        
        // reverse
        list9.reverse();
        print_test_result("reverse", list9, "5 2 4 2 3 2 1");
        
        // concatenate
        ListOperationsKit<int> list10 = {100, 200};
        list9.concatenate(list10);
        print_test_result("concatenate", list9, "5 2 4 2 3 2 1 100 200");
        
        separator("8. Random Fill Tests");
        
        ListOperationsKit<int> list11;
        list11.random_append(5, 1, 10);
        print_test_result("random_append(5, 1-10)", list11);
        
        separator("9. Size Function Compatibility Tests");
        
        std::cout << "size(): " << list9.size() << "\n";
        std::cout << "get_size(): " << list9.get_size() << "\n";
        std::cout << "length(): " << list9.length() << "\n";
        std::cout << "empty(): " << (list9.empty() ? "Yes" : "No") << "\n";
        
        separator("10. Operator Overloading Tests");
        
        ListOperationsKit<int> list12 = {1, 2, 3};
        ListOperationsKit<int> list13 = {1, 2, 3};
        ListOperationsKit<int> list14 = {1, 2, 4};
        
        std::cout << "list12 == list13: " << (list12 == list13 ? "Yes" : "No") << "\n";
        std::cout << "list12 != list14: " << (list12 != list14 ? "Yes" : "No") << "\n";
        std::cout << "list12 < list14: " << (list12 < list14 ? "Yes" : "No") << "\n";
        
        // Assignment operators
        list12 = {10, 20, 30, 40};
        print_test_result("Assignment {10,20,30,40}", list12);
        
        list13 = list12;
        print_test_result("Copy assignment", list13);
        
        list14 = std::move(list12);
        print_test_result("Move assignment", list14);
        std::cout << "Original object empty after move assignment: " << (list12.empty() ? "Yes" : "No") << "\n";
        
        separator("11. Exception Handling Tests");
        
        ListOperationsKit<int> empty_list;
        
        try {
            empty_list.front();
        } catch (const std::out_of_range& e) {
            std::cout << "front() empty list exception: " << e.what() << "\n";
        }
        
        try {
            empty_list.pop_front();
        } catch (const std::out_of_range& e) {
            std::cout << "pop_front() empty list exception: " << e.what() << "\n";
        }
        
        try {
            list14.get(999);
        } catch (const std::out_of_range& e) {
            std::cout << "get(999) out of bounds exception: " << e.what() << "\n";
        }
        
        separator("12. Stack and Queue Tests");
        
        // Stack test
        LinkedStack<int> stack;
        stack.push(10);
        stack.push(20);
        stack.push(30);
        
        std::cout << "Stack test:\n";
        std::cout << "  size: " << stack.size() << "\n";
        std::cout << "  top: " << stack.top() << "\n";
        
        while (!stack.empty()) {
            std::cout << "  pop: " << stack.top() << "\n";
            stack.pop();
        }
        
        // Queue test
        LinkedQueue<int> queue;
        queue.push(100);
        queue.push(200);
        queue.push(300);
        
        std::cout << "Queue test:\n";
        std::cout << "  size: " << queue.size() << "\n";
        std::cout << "  front: " << queue.front() << "\n";
        std::cout << "  back: " << queue.back() << "\n";
        
        while (!queue.empty()) {
            std::cout << "  pop: " << queue.front() << "\n";
            queue.pop();
        }
        
        separator("13. Performance Tests");
        
        auto start = std::chrono::high_resolution_clock::now();
        
        ListOperationsKit<int> perf_list;
        const int N = 10000;
        
        // Insertion performance test
        for (int i = 0; i < N; ++i) {
            perf_list.push_back(i);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Insert " << N << " elements time: " << duration.count() << " microseconds\n";
        std::cout << "Final size: " << perf_list.size() << "\n";
        
        // Clear test
        perf_list.clear();
        std::cout << "Size after clear(): " << perf_list.size() << "\n";
        
        separator("14. String Type Tests");
        
        ListOperationsKit<std::string> str_list = {"Hello", "Modern", "C++", "World"};
        print_test_result("String list", str_list);
        
        str_list.append("!", "Amazing", "Code");
        print_test_result("Append strings", str_list);
        
        str_list.sort();
        print_test_result("String sorting", str_list);
        
        separator("15. Manual Reverse Iteration Tests");
        
        ListOperationsKit<int> reverse_test = {1, 2, 3, 4, 5};
        std::cout << "Using index reverse iteration: ";
        for (int i = static_cast<int>(reverse_test.size()) - 1; i >= 0; --i) {
            std::cout << reverse_test[i] << " ";
        }
        std::cout << "\n";
        
        std::cout << "Using print_reverse(): ";
        reverse_test.print_reverse();
        
        separator("Test Complete");
        
        std::cout << "All tests executed successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred during testing: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}