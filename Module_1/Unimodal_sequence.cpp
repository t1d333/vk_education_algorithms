//Дан массив целых чисел А[0..n-1].
//Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают.
//Найти m за O( log m ).
//2 ≤ n ≤ 10000.
#include <iostream>

size_t binary_search(int arr[], size_t left_bound, size_t right_bound) {
	size_t mid = (left_bound + right_bound) / 2;
	while (left_bound < right_bound) {
		mid = (left_bound + right_bound) / 2;
		if ((left_bound - right_bound) == 1) {
			return (arr[left_bound] > arr[right_bound]) ? left_bound : right_bound; 
		}
		if ((arr[mid] > arr[mid + 1]) && (arr[mid] > arr[mid - 1])) {
			return mid;
		} else if ((arr[mid] < (arr[mid + 1]))) {
			left_bound = mid + 1;
		} else {
			right_bound = mid - 1;
		}	
	}
	return left_bound;
}


size_t exponential_search(int arr[], size_t len) {
	size_t left_bound = 0;
	size_t right_bound = 0;
	bool flag = true;
	for (int i = 1; (1 << i) <= len; i++) {
		left_bound = (1 << (i - 1)) - 1;
		right_bound = (1 << i) - 1;
		if (arr[(1 << i) - 2] > arr[(1 << i) - 1]) {
			flag = false;
			break;
		} 
	}
	right_bound = flag ? len - 1 : right_bound;
	return binary_search(arr, left_bound, right_bound);
}


int main() {
	size_t len = 0;
	std::cin >> len;
	int arr[len];	
	for (int i = 0; i < len; i++) {
		std::cin >> arr[i];
	}
	std::cout << exponential_search(arr, len) << std::endl;
}
