#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/types.h>
#include <type_traits>
#include <utility>
#include <vector>


class HashMap {
private:
  struct HashMapItem {
    bool empty;
    bool deleted;
    std::string key;
    HashMapItem(const std::string& k) : empty(false), deleted(false), key(k) {}
    HashMapItem() : empty(true), deleted(false) {}
  };
  size_t hash(const std::string &str, size_t k);
  size_t size;
  size_t cap;
  void grow();

public:
  std::vector<HashMapItem> buf;
  HashMap() : size(0), cap(8), buf(std::vector<HashMapItem>(8)) {}
  ~HashMap(){};
  bool insert(const std::string &key);
  bool find(const std::string &key);
  bool erase(const std::string &key);
};



size_t HashMap::hash(const std::string &str, size_t k)  {
  size_t hash = 0;
  for (char a : str) {
    hash = (hash * k + a) % cap;
  }
  return hash;
}

void HashMap::grow() {
  size_t oldSize = size;
  size_t oldCap = cap;

  cap *= 2;
  size = 0;

  std::vector<HashMapItem> oldBuf = buf;
  buf = std::vector<HashMapItem>(cap);
  for (size_t i = 0; i < oldCap; i++) {
    if (!oldBuf[i].deleted && !oldBuf[i].empty) {
      insert(oldBuf[i].key);
    }
  }
}

bool HashMap::insert(const std::string &key) {
  size_t h1 = hash(key, 13);
  size_t h2 = hash(key, 31);
  int pos = -1;
  for (size_t i = 0; i < cap; i++) {
    size_t j = (h1 + i * (h2 + h2 % 2 + 1)) % cap;

    if (buf[j].empty) {
      if (pos != -1) {
        buf[pos].key = key;
        buf[pos].deleted = false;
      } else {
        buf[j].key = key;
        buf[j].empty = false;
      }
      ++size;
      if ((4 * size) >= (3 * cap)) {
        grow();
      }
      return true;
    }

  	if ((pos == -1 ) && buf[j].deleted) {
      pos = j;
    }

    if (!buf[j].deleted && (buf[j].key == key)) {
      return false;
    }

  }
  return false;
}

bool HashMap::find(const std::string &key) {
  size_t h1 = hash(key, 13);
  size_t h2 = hash(key, 31);
  for (size_t i = 0; i < cap; i++) {
    size_t j = (h1 + i * (h2 + h2 % 2 + 1)) % cap;

    if (buf[j].empty) {
      return false;
    }

    if (!buf[j].deleted && (buf[j].key == key)) {
      return true;
    }
  }
  return false;
}

bool HashMap::erase(const std::string &key) {
  size_t h1 = hash(key, 13);
  size_t h2 = hash(key, 31);

  for (size_t i = 0; i < cap; i++) {
    size_t j = (h1 + i * (h2 + h2 % 2 + 1)) % cap;

    if (buf[j].empty) {
      return false;
    }

    if (!buf[j].deleted && (buf[j].key == key)) {
      buf[j].deleted = true;
      --size;
      return true;
    }
  }

  return false;
}


int main() {
  HashMap h;
  std::string key;
  char operation;
  while (std::cin >> operation >> key) {
    switch (operation) {
    case '+':
      std::cout << (h.insert(key) ? "OK" : "FAIL") << '\n';
      break;
    case '-':
      std::cout << (h.erase(key) ? "OK" : "FAIL") << '\n';
      break;
    case '?':
      std::cout << (h.find(key) ? "OK" : "FAIL") << '\n';
      break;
    }
  }
}
