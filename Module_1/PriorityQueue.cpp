/*

Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке возрастания посещаемости.
Количество заходов и идентификаторы пользователей не повторяются.

Требования:

Время работы O(N * logK)
Куча должна быть реализована в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.
Куча должна быть динамической.
*/


#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <cassert>

struct User {
    size_t id;
    size_t freq;
};


class UserComparator {
    public:
        bool operator()(const User& lhs, const User& rhs) {
            return lhs.freq < rhs.freq;
        }
};

template <typename T, class Comparator = std::less<T>>
class Priority_queue {
    private:
        T* buffer;
        Comparator cmp;
        size_t len;
        size_t cap;
        void grow();
        void sift_up(size_t i);
        void sift_down(size_t i);
    public:
        Priority_queue(): buffer(nullptr), len(0), cap(0) {};

        Priority_queue(const Priority_queue<T, Comparator>& other);

        Priority_queue<T, Comparator>& operator=(const Priority_queue<T, Comparator>& other);

        T extract_min();
        bool is_empty();
        T top() const;
        void insert(T val);
        ~Priority_queue() {delete[] buffer;}
};

template<typename T, typename Comparator>
void Priority_queue<T, Comparator>::grow() {
    if (cap == 0) {
        buffer = new T[5];
        cap = 5;
    } else {
        T* new_buffer = new T[cap * 2];
        std::copy(buffer, buffer + cap, new_buffer);
        delete[] buffer;
        buffer = new_buffer;
        cap *= 2;
    }
}

bool less(User u1, User u2) {
    return u1.freq < u2.freq;
}

template<typename T, typename Comparator>
Priority_queue<T, Comparator>::Priority_queue(const Priority_queue<T, Comparator>& other)
    : cap(other.cap), len(other.len), buffer(new T[other.cap]) {
    std::copy(other.buffer, other.buffer + cap, buffer);
}

template<typename T, typename Comparator>
bool Priority_queue<T, Comparator>::is_empty() {
    return len == 0;
}


template<typename T, typename Comparator>
Priority_queue<T, Comparator>& Priority_queue<T, Comparator>::operator=(const Priority_queue<T, Comparator>& other) {
    if (this != &other) {
        delete[] buffer;
        buffer = new T[other.cap];
        cap = other.cap;
        len = other.len;
        std::copy(other.buffer, other.buffer + other.cap, buffer);
    }
    return *this;
}
template<typename T, typename Comparator>
void Priority_queue<T, Comparator>::sift_up(size_t i) {
    while (i > 0) {
    if (cmp(buffer[i], buffer[(i - 1) / 2])) {
            std::swap(buffer[i], buffer[(i - 1) / 2]);
            i = (i - 1) / 2;
        } else {
            break;
        }
    }
}

template<typename T, typename Comparator>
void Priority_queue<T, Comparator>::sift_down(size_t i) {
   size_t left_ind = 2 * i + 1;
   size_t right_ind = 2 * i + 2;
   size_t min_ind = ((left_ind < len) && cmp(buffer[left_ind], buffer[i])) ? left_ind : i;
   min_ind =  ((right_ind < len) && cmp(buffer[right_ind], buffer[min_ind])) ? right_ind : min_ind;
   if (min_ind != i) {
       std::swap(buffer[min_ind], buffer[i]);
       sift_down(min_ind);
   }
}



template<typename T, typename Comparator>
T Priority_queue<T, Comparator>::top() const {
   assert(len > 0); 
   return buffer[0]; 
}

template<typename T, typename  Comparator>
void Priority_queue<T, Comparator>::insert(T val) {
    if (len == cap) {
       grow();
    }
    buffer[len++] = val;
    sift_up(len - 1);
}

template<typename T, typename Comparator>
T Priority_queue<T, Comparator>::extract_min() {
    assert(len != 0);
    T tmp = buffer[0]; 
    std::swap(buffer[0], buffer[--len]); 
    sift_down(0);
    return tmp;
}

int main() {
    Priority_queue<User, > q;
    size_t N = 0;
    size_t K = 0;
    std::cin >> N >> K;
    for (size_t i = 0; i < N; i++) {
        User usr;
        std::cin >> usr.id >> usr.freq;
        q.insert(usr);
        if (i >= K) {
            q.extract_min();
        }
    }
    while(!q.is_empty()) {
        std::cout << q.extract_min().id << " ";
    }
    std::cout << std::endl;
}




