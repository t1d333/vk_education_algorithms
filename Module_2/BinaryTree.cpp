#include <cstddef>
#include <functional>
#include <iostream>
#include <vector>
#include <stack>

template <typename T, typename Comparator = std::less<T>> class BinaryTree {
private:
  struct Node {
    Node *parent;
    Node *left;
    Node *right;
    T key;
    Node(T k) : key(k), parent(nullptr), left(nullptr), right(nullptr) {}
  };

  Node *root;
  Comparator comparator;
  static void deleteNode(Node *n) { delete n; }
  void copyTree(Node *root);
  std::vector<T> postOrder(void (*operation)(Node *));
public:
  BinaryTree() : root(nullptr) {}
  BinaryTree(const BinaryTree<T, Comparator> &other);
  BinaryTree<T, Comparator> &operator=(const BinaryTree<T, Comparator> &other);
  ~BinaryTree() { postOrder(deleteNode); }
  void insert(const T& key);
  std::vector<T> getKeys();
};

template <typename T, typename Comparator>
std::vector<T> BinaryTree<T, Comparator>::getKeys() {
  return postOrder([] (Node *n) {});
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::copyTree(Node *otherRoot) {
  std::stack<Node *> s1;
  std::stack<Node *> s2;
  s1.push(otherRoot);

  while (!s1.empty()) {
    Node *cur = s1.top();
    s1.pop();
    s2.push(cur);

    if (cur->left) {
      s1.push(cur->left);
    }

    if (cur->right) {
      s1.push(cur->right);
    }
  }
  while (!s2.empty()) {
    insert(s2.top()->key);
    s2.pop();
  }
}

template <typename T, typename Comparator>
BinaryTree<T, Comparator>::BinaryTree(const BinaryTree<T, Comparator> &other)
    : root(nullptr) {
  copyTree(other.root);
}

template <typename T, typename Comparator>
BinaryTree<T, Comparator> &
BinaryTree<T, Comparator>::operator=(const BinaryTree<T, Comparator> &other) {

  if (&other != this) {
    postOrder(deleteNode);

    root = nullptr;

    copyTree(other.root);
  }
  return *this;
}

template <typename T, typename Comparator>
std::vector<T> BinaryTree<T, Comparator>::postOrder(void (*operation)(Node *)) {
  if (!root) {
    return std::vector<T>();
  }
  std::stack<Node *> s1;
  std::stack<Node *> s2;
  std::vector<T> keys;

  s1.push(root);

  while (!s1.empty()) {
    Node *cur = s1.top();
    s1.pop();
    s2.push(cur);

    if (cur->left) {
      s1.push(cur->left);
    }

    if (cur->right) {
      s1.push(cur->right);
    }
  }
  while (!s2.empty()) {
    keys.push_back(s2.top()->key);
    operation(s2.top());
    s2.pop();
  }
  return keys;
}

template <typename T, typename Comparator>
void BinaryTree<T, Comparator>::insert(const T& key) {
  if (!root) {
    root = new Node(key);
    return;
  }

  Node *cur = root;
  Node *prev = nullptr;
  while (cur) {
    prev = cur;
    if (comparator(key, cur->key)) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }

  Node *tmp = new Node(key);
  tmp->parent = prev;
  if (comparator(key, prev->key)) {
    prev->left = tmp;
  } else {
    prev->right = tmp;
  }
}

int main() {

  BinaryTree<int> b;
  size_t n = 0;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    int value = 0;
    std::cin >> value;
    b.insert(value);
  }

  for (int k : b.getKeys()) {
    std::cout << k << " ";
  }
  std::cout << std::endl;
}
