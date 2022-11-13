#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstddef>
#include <cmath>
#include <cstdint>

template<typename  T>
size_t Partition(T* arr, size_t left, size_t right, bool (*cmp)(const T &l, const T &r)) {
    srand(time(nullptr));
    size_t pivot =  left + rand() % (right - left);
    std::swap(arr[left], arr[pivot]);
    size_t i = right - 1;
    size_t j = right - 1;
    while (j > left) {
        if (arr[j] < arr[left]) {
            --j;
        } else {
            std::swap(arr[i], arr[j]);
            --i;
            --j;
        }
    }
    std::swap(arr[left], arr[i]);
    return i;
}

template <typename T>
size_t QuickSelect(T* arr, size_t len, size_t pos, bool (*cmp)(const T &l, const T &r)) {
    size_t left = 0;
    size_t right = len;
    size_t pivot = 0;
    while ((pivot = Partition(arr, left, right, cmp))  != pos) {
        if (pivot > pos) {
            right = pivot;
        } else {
             left = pivot + 1;
        }
    }
    return arr[pivot];
}

bool Cmp(const uint64_t& l, const uint64_t& r) {
    return l < r;
}

int main() {
    size_t len = 0;
    std::cin >> len;
    uint64_t* arr = new size_t[len];
    for (size_t i = 0; i < len; i++) {
        std::cin >> arr[i];
    }
    std::cout << QuickSelect(arr, len, std::floor(len * 0.1), Cmp) << std::endl;
    std::cout << QuickSelect(arr, len, len / 2, Cmp) << std::endl;
    std::cout << QuickSelect(arr, len, std::floor(len * 0.9), Cmp) << std::endl;

}
