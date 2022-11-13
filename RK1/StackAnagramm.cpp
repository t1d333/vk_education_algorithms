#include <cstddef>
#include <iostream>
#include <cassert>

class Stack{
    private:
        char* buffer;
        size_t len;
        size_t cap;
    public:
        Stack(): buffer(new char[5]), len(0), cap(5) {};
        Stack(const Stack& other);
        Stack& operator=(const Stack& other);
        void Push(char c);
        char Pop();
        bool Empty();
        char Top();
        ~Stack() {delete[] buffer;}

};

bool Stack::Empty() {
    return len == 0;
}

Stack::Stack(const Stack& other) : len(other.len), cap(other.cap) {
   buffer = new char[cap]; 
   std::copy(other.buffer, other.buffer + cap, buffer);
}


Stack& Stack::operator=(const Stack& other) {
    if (this != &other) {
        cap = other.cap;
        len = other.len;
        delete[] buffer;
        buffer = new char[cap];
        std::copy(other.buffer, other.buffer + cap, buffer);
    }
    return *this;
}

char Stack::Pop() {
    assert(len != 0);
    return buffer[--len];
}
char Stack::Top() {
    assert(len != 0);
    return buffer[len - 1];
}
void Stack::Push(char c) {
    if (len == cap) {
        char* new_buf = new char[cap * 2];
        std::copy(buffer, buffer + cap, new_buf);
        cap *= 2;
        delete [] buffer;
        buffer = new_buf;
    }
    buffer[len++] = c;
}




int main() {
    std::string s1 = "";
    std::string s2 = ""; 
    std::cin >> s1 >> s2;
    Stack stack; 
    size_t counter = 0;
    for (size_t i = 0; i < s1.length(); i++) {
        stack.Push(s1[i]);
        for (; !stack.Empty() && (stack.Top() == s2[counter]); ++counter) {
            stack.Pop();
        }
    }
    std::cout << (stack.Empty() ? "YES" : "NO") << std::endl;
}
