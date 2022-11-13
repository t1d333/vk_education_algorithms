/*

Реализовать дек с динамическим зацикленным буфером.

Обрабатывать команды push * и pop *.
Формат ввода

В первой строке количество команд n. n ≤ 1000000.

Каждая команда задаётся как 2 целых числа: a b.

a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back

Если дана команда pop *, то число b - ожидаемое значение. Если команда pop * вызвана для пустой структуры данных, то ожидается “-1”.
*/
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cassert>

class Dequeue {
	private:
		size_t len;
		size_t head;
		size_t tail;
		size_t cap;
		int32_t* buffer;
		void grow();
	public:	
		size_t size() const;	
		Dequeue(const Dequeue& other);
		Dequeue operator=(const Dequeue& other);
		Dequeue() :buffer(nullptr), head(0), tail(0), len(0), cap(0) {}
		bool isEmpty() const;
		void push_back(int32_t);
		void push_front(int32_t);
		int32_t pop_back();
		int32_t pop_front();
		~Dequeue() {delete[] buffer;}
};

enum commands{
	PUSH_FRONT = 1,
	POP_FRONT,
	PUSH_BACK,
	POP_BACK,
};

bool Dequeue::isEmpty() const {
	return len == 0;
}

size_t Dequeue::size() const {
	return len;
}

Dequeue Dequeue::operator=(const Dequeue& other) {
	if (this != &other) {
		if (buffer != nullptr) {
			delete[] buffer;
		}
		len = other.len;
		head = other.head;
		cap = other.cap;
		tail = other.tail;
		buffer = new int32_t[len];
		std::copy(other.buffer, other.buffer + len, buffer);
	}	
	return *this;
}
Dequeue::Dequeue(const Dequeue& other): 
	len(other.len), head(other.head), tail(other.tail), cap(other.cap) {
	buffer = new int32_t[len];
	std::copy(other.buffer, other.buffer + len, buffer);
}

void Dequeue::grow() {
	if (cap == 0) {
		cap = 5;
		buffer = new int32_t[5];
		tail = 5;
		head = -1;
	} else {
		int32_t* new_buffer = new int32_t[cap * 2];
		if (head < tail) {
			int32_t new_tail =  cap * 2 - (cap - tail);
			std::copy(buffer, buffer + head + 1, new_buffer);
			std::copy(buffer + tail, buffer + cap, new_buffer + new_tail);
			tail = new_tail;
		} else {
			std::copy(buffer, buffer + head + 1, new_buffer);
		}
		delete[] buffer;
		cap *= 2;
		buffer = new_buffer;
	} 
} 


void Dequeue::push_front(int32_t value) {
	if (len == cap) {
		grow();
	}
	head = (head + 1) % cap;
	buffer[head] = value;
	++len;
}

void Dequeue::push_back(int32_t value) {
	if (len == cap) {
		grow();
	}
	tail = ((tail - 1) + cap) % cap;
	buffer[tail] = value;
	++len;
}

int32_t Dequeue::pop_back() {
	assert(!isEmpty());
	size_t tmp = tail;
	tail = (tail + 1) % cap;
	--len;
	return buffer[tmp % cap];
}

int32_t Dequeue::pop_front() {
	assert(!isEmpty());
	size_t tmp = head;
	head = ((head - 1) + cap) % cap;
	--len;
	return buffer[(tmp + cap) % cap];	
}




int main() {
	Dequeue q;
	std::string result = "YES";	
	size_t n = 0;
	std::cin >> n;
	for (size_t i = 0; i < n; i++) {
		size_t a = 0;
		int32_t b = 0;
		std::cin >> a >> b;
		switch (a) {
			case PUSH_FRONT:
				q.push_front(b);
				break;
			case POP_FRONT:
				result = ((b == -1) && (q.isEmpty())) || (q.pop_front() == b) ? "YES": "NO";
				break;
			case PUSH_BACK:
				q.push_back(b);
				break;
			case POP_BACK:
				result = ((b == -1) && (q.isEmpty())) || (q.pop_back() == b) ? "YES": "NO";
			
		}
	}
	std::cout << result << std::endl;
}

