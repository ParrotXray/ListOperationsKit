#include <iostream>
#include <algorithm>
#include <format>
#include "ListOperationsKit.h"

void quick_sort(int begin, int end, ListOperationsKit<int>& list) {
    if(begin < end) {
        int i = begin, j = end, pivot = list.get(begin);
        do {
            while (list[i] < pivot) ++i;
            while (list[j] > pivot) --j;
            if (i <= j) {
                list.swap(i, j);
                ++i;
                --j;
            }
        } while(i <= j);
        quick_sort(begin, j, list);
        quick_sort(i, end, list);
    }
}

void merge(int begin, int mid, int end, ListOperationsKit<int>& list) {
    int i = begin, j = mid + 1, k = 0;
    ListOperationsKit<int> temp;
    while (i <= mid && j <= end) {
        if (list.get(i) < list[j]) {
            temp.append(list[i]);
            ++i;
        } else {
            temp.append(list[j]);
            ++j;
        }
    }
    while (i <= mid) {
        temp.append(list[i]);
        ++i;
    }
    while (j <= end) {
        temp.append(list[j]);
        ++j;
    }
    for (int n = begin; n <= end; ++n) {
        list[n] = temp[k];
        ++k;
    }
}

void merge_sort(int begin, int end, ListOperationsKit<int>& list) {
    if (begin < end) {
        int mid = (begin + end) / 2;
        merge_sort(begin, mid, list);
        merge_sort(mid + 1, end, list);
        merge(begin, mid, end, list);
    }
}

void stooge_sort(int begin, int end, ListOperationsKit<int>& list) {
    if (list.get(begin) > list(end)) {
        list.swap(begin, end);
    }
    if (end - begin + 1 > 2) {
        int t = (end - begin + 1) / 3;
        stooge_sort(begin, end - t, list);
        stooge_sort(begin + t, end, list);
        stooge_sort(begin, end - t, list);
    }
}

int main() {
    ListOperationsKit<int> list_1, list_2, list_3;

    list_1.random_append(10);
    list_2.random_append(10, 2, 50);
    list_3.append(99, 53, 21, 8, 9, 10, 11, 12, 65, 94);

    std::cout << list_1 << std::endl;
    std::cout << list_2 << std::endl;
    std::cout << list_3 << std::endl;

    std::cout << std::endl;

    quick_sort(0, list_1.length(), list_1);
    merge_sort(0, list_2.length(), list_2);
    stooge_sort(0, list_3.length(), list_3);

    std::cout << list_1 << std::endl;
    std::cout << list_2 << std::endl;
    std::cout << list_3 << std::endl;

    return 0;
}