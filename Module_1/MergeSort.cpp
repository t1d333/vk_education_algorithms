/*
В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные моменты времени. Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.
*/
#include <algorithm>
#include <climits>
#include <cstddef>
#include <functional>
#include <iostream>
#include <bits/stdc++.h> 

struct Customer {
    int in; 
    int out;
};


template<typename T>
T* Merge(T* first_arr, T* second_arr,  size_t first_size ,size_t second_size,  bool (*cmp)(const T &l, const T &r)) {
    T* buffer = new T[first_size + second_size]; 
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    for (; (i < first_size) && (j < second_size); k++) {
        if (cmp(first_arr[i], second_arr[j])) {
            buffer[k] = first_arr[i];
            ++i;
        } else {
            buffer[k] = second_arr[j];
            ++j; 
        }
    }

    for (; i < first_size; ++i) {
        buffer[k] = first_arr[i];
        ++k;
    }

    for (; j < second_size; ++j) {
        buffer[k] = second_arr[j];
        ++k;
    }
    return buffer;

}


template<typename T>
void MergeSort(T* arr, size_t size, bool (*cmp)(const T &l, const T &r)) {
    if (size <= 1) {
        return;
    }
    size_t left_len = size / 2;
    size_t right_len = size  - left_len;
    MergeSort(arr, left_len, cmp);
    MergeSort(arr + left_len, right_len, cmp);
    T* tmp = Merge(arr, arr + left_len, left_len, right_len, cmp); 
    std::copy(tmp, tmp + size, arr);
    delete [] tmp;
}

bool CustomerComparator(const Customer& l, const Customer& r) {
    if (l.out < r.out) {
        return true;
    } else if (l.out == r.out) {
        return l.in > r.in;
    }
    return false;
}

int main() {
    size_t N;
    std::cin >> N;
    Customer* arr = new Customer[N];
    for (size_t i = 0; i < N; ++i) {
        std::cin >> arr[i].in;
        std::cin >> arr[i].out;
    }
    MergeSort(arr, N, CustomerComparator);
    int t1 = arr[0].out - 1;
    int t2 = arr[0].out;
    size_t counter = 2;
    for (size_t i = 1; i < N; i++) {
        if ((t1 < arr[i].in) && (t2 < arr[i].in)) {
            counter += 2;
            t1 = arr[i].out - 1;
            t2 = arr[i].out;
        } else if (t1 < arr[i].in) {
            ++counter;
            t1 = arr[i].out;
        } else if (t2 < arr[i].in) {
            ++counter;
            t2 = arr[i].out;
        }
    }
    std::cout << counter << std::endl;
}


