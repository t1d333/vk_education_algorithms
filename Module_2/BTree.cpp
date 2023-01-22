/*
 *
Постройте B-дерево минимального порядка t и выведите его по слоям.
В качестве ключа используются числа, лежащие в диапазоне [0..232-1]

Требования:

B-дерево должно быть реализовано в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.

*/
#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

template <typename T, typename Comparator = std::less<T>> class BTree {

private:
  struct Node {
    Node(bool leaf) : leaf(leaf) {}
    std::vector<T> keys;
    std::vector<Node *> children;
    bool leaf;
    ~Node() {
      for (size_t i = 0; i < children.size(); ++i) {
        delete children[i];
      }
    }
  };

  size_t minDegree;
  void split(Node *node, size_t n) {
    Node *child = node->children[n];
    size_t size = child->keys.size();
    size_t mid = size / 2;
    T midKey = child->keys[mid];
    Node *newNode = new Node(child->leaf);
    newNode->keys.resize(mid);

    for (size_t i = 1; i <= mid; ++i) {
      newNode->keys[mid - i] = child->keys[size - i];
      child->keys.pop_back();
    }

    child->keys.pop_back();

    if (!newNode->leaf) {
      newNode->children.resize(mid + 1);
      for (size_t i = 0; i <= mid; ++i) {
        newNode->children[mid - i] = child->children[size - i];
        child->children.pop_back();
      }
    }

    node->children.resize(node->children.size() + 1);
    for (size_t i = node->children.size() - 2; i > n; --i) {
      node->children[i + 1] = node->children[i];
    }

    node->children[n + 1] = newNode;

    node->keys.resize(node->keys.size() + 1);

    for (size_t i = node->keys.size() - 1; i > n; --i) {
      node->keys[i] = node->keys[i - 1];
    }
    node->keys[n] = midKey;
  }

  void insertAux(Node *node, T key) {
    int pos = node->keys.size() - 1;
    if (node->leaf) {
      node->keys.resize(node->keys.size() + 1);
      while ((pos >= 0) && (key < node->keys[pos])) {
        node->keys[pos + 1] = node->keys[pos];
        --pos;
      }
      node->keys[pos + 1] = key;
    } else {
      while ((pos >= 0) && (key < node->keys[pos])) {
        --pos;
      }
      if (isFull(node->children[pos + 1])) {
        split(node, pos + 1);
        if (key > node->keys[pos + 1]) {
          ++pos;
        }
      }
      insertAux(node->children[pos + 1], key);
    }
  }

  bool isFull(Node *n) { return n->keys.size() == (2 * minDegree - 1); }

  Node *root;

public:
  BTree(size_t degree) : minDegree(degree), root(nullptr) {}

  void insert(T key) {
    if (!root) {
      root = new Node(true);
    }

    if (isFull(root)) {
      Node *newRoot = new Node(false);
      newRoot->children.push_back(root);
      root = newRoot;
      split(root, 0);
    }
    insertAux(root, key);
  }

  void printTree() {
    std::queue<Node *> q1;
    std::queue<Node *> q2;
    q1.push(root);
    while (true) {
      if (q1.empty() && q2.empty()) {
        break;
      }

      if (q1.empty()) {
        while (!q2.empty()) {
          q1.push(q2.front());
          q2.pop();
        }
      }
      while (!q1.empty()) {
        Node *cur = q1.front();
        q1.pop();
        for (T k : cur->keys) {
          std::cout << k << " ";
        }

        for (Node *n : cur->children) {
          q2.push(n);
        }
      }
      std::cout << std::endl;
    }
  }

  void copyTree(Node *n) {
    if (n) {
      for (const T &key : n->keys) {
        insert(key);
      }
      for (Node *node : n->children) {
        copyTree(node);
      }
    }
  }

  BTree(const BTree &other) : minDegree(other.minDegree), root(nullptr) {
    copyTree(other.root);
  };

  BTree &operator=(const BTree &other) {
    if (&other != this) {
      delete root;
      root = nullptr;
      copyTree(other.root);
    }
    return *this;
  }

  ~BTree() { delete root; }
};

int main(int argc, char *argv[]) {
  size_t n = 0;
  std::cin >> n;
  BTree<int> b(n);
  int k = 0;
  while (std::cin >> k) {
    b.insert(k);
  }
  b.printTree();
  return 0;
}
