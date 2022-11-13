#include <cstddef>
#include <iostream>

size_t lower_bound(int* arr, int val, size_t l, size_t r) {
    size_t mid = (l + r) / 2;
    if (l >= r) {
        return l;
    }
    if (arr[mid] == val) {
        return mid; 
    } else if (arr[mid] < val) {
        return lower_bound(arr, val, mid + 1, r);
    } else {
        return lower_bound(arr, val, l, mid);
    } 
}

int main() {
    size_t len = 0;
    int* arr = nullptr;
    int val = 0;
    std::cin >> len;
    arr = new int[len];
    for (size_t i = 0; i < len; i++) {
        std::cin >> arr[i];
    }
    std::cin >> val;
    std::cout << lower_bound(arr, val, 0, len) << std::endl;
    delete[] arr;
}

