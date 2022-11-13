//Инвертируйте значение бита в числе N по его номеру K.
//Необходимо использование битовых операций.
//Использование арифметических операций запрещено. 

#include <cstdint>
#include <iostream>

uint32_t invert_bit(uint32_t number, uint32_t bit_position) { 
	return (number ^ (1 << bit_position));
}

int main() {
	uint32_t number = 0;
	uint32_t bit_position = 0;
	std::cin >> number >> bit_position;
	std::cout << invert_bit(number, bit_position) << std::endl;
}
