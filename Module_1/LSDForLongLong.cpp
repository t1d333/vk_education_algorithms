#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>

void CountingSort(uint64_t* arr, size_t size, size_t radix) {
    int tmp[256]{0};

    for (size_t i = 0; i < size; ++i) {
        ++tmp[(arr[i] >> (8 * radix)) & 0xFF];
    }
    for (size_t i = 1; i < 256; ++i) {
        tmp[i] += tmp[i - 1];
    }

    uint64_t buffer[size];
    
    for (size_t i = size - 1; i >= 0; --i) {
        buffer[--tmp[(arr[i] >> (8 * radix)) & 0xFF]]  = arr[i];  
        if (i == 0) {
            break;
        }
    }
    std::copy(buffer, buffer + size, arr);
}


void RadixSort(uint64_t* arr, size_t size) {
    for (size_t i = 0; i < 8; ++i) {
        CountingSort(arr, size, i);
    }
}

int main() {
    size_t size = 0;
    std::cin >> size;
    uint64_t* arr = new uint64_t[size];
    for (size_t i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
    RadixSort(arr, size); 
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    delete[] arr;
}
