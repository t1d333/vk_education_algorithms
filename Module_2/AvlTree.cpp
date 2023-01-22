#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>

template <typename T, typename Comparator=std::less<T>> class AvlTree {
private:
  struct Node {
    Node *right;
    Node *left;
    T key;
    uint8_t height;
    size_t nodesCount; 
    explicit Node(T _key)
        : right(nullptr), left(nullptr), key(_key), height(1), nodesCount(1)
          {}
    ~Node() {
      delete left;
      delete right;
    }
  };

  Comparator comp;

  void fixHeight(Node *node) { 
    node->height = std::max(height(node->left), height(node->right)) + 1;
    node->nodesCount = getNodesCount(node->left) + getNodesCount(node->right) + 1;
  }

  uint8_t height(Node* node) {
    if (!node) {
      return 0;
    }
    return node->height;
  }

  size_t getNodesCount(Node* node) {
    if (!node) {
      return 0;
    }
    return node->nodesCount;
  }

  int bfactor(Node* node) {
    return height(node->right) - height(node->left);
  }

  Node *balance(Node *n) {
    fixHeight(n); 
    int bf  = bfactor(n);
    switch (bf) {
      case 2:
        if (bfactor(n->right) < 0) {
          n->right = rotateRight(n->right);
        }
        return rotateLeft(n);
        break;
      case -2:
        if (bfactor(n->left) > 0) {
          n->left = rotateLeft(n->left);
        }
        return rotateRight(n);
        break;
      default:
        return n;
        break;
    }
  }

  Node* rotateLeft(Node* n) {
    Node* tmp = n->right;
    n->right = tmp->left;
    tmp->left = n;
    fixHeight(n);
    fixHeight(tmp);
    return tmp;
  }

  Node* rotateRight(Node* n) {
    Node* tmp = n->left;
    n->left = tmp->right;
    tmp->right = n;
    fixHeight(n);
    fixHeight(tmp);
    return tmp;
  } 

  Node *insertNode(Node *node, const T &key) {
    if (!node) {
      return new Node(key);
    }

    if (comp(key, node->key)) {
      node->left = insertNode(node->left, key);
    }

    if (comp(node->key, key)) {
      node->right = insertNode(node->right, key);
    }

    return balance(node);
  }

  Node *eraseNode(Node *node, const T &key) {
    if (!node) {
      return nullptr;
    }

    if (comp(key, node->key)) {
      node->left = eraseNode(node->left, key);
    } else if (comp(node->key, key)) {
      node->right = eraseNode(node->right, key);
    } else {
      Node *left = node->left;
      Node *right = node->right;

      if (!right) {
        node->left = nullptr;
        delete node;
        return left;
      }
      node->right = findAndRemoveMin(right, node);
    }
    return balance(node);
  }

  Node *findAndRemoveMin(Node *node, Node* tmp) {
    if (! node->left) {
      tmp->key = node->key;
      Node* t = node->right;
      node->right = nullptr;
      delete node;
      return t;
    }

    node->left = findAndRemoveMin(node->left, tmp);
    return balance(node);
  }
  
  T findStatRec(Node* n, size_t k) {

    if (getNodesCount(n->left) == k) {
      return n->key;
    }
    if (n->left && (getNodesCount(n->left) > k)) {
      return findStatRec(n->left, k);
    } else {
      return findStatRec(n->right, k - getNodesCount(n->left) - 1);
    }
    
  }

  void copyTree(Node* n) {
    if (n) {
      insert(n->key);
      copyTree(n->left);
      copyTree(n->right);
    }
  }

public:
  AvlTree() : root(nullptr) {}

  AvlTree(const AvlTree<T, Comparator>& other) : root(nullptr) {
    copyTree(other.root);
  }

  Node *root;
  void insert(const T &key) { root = insertNode(root, key); }
  void erase(const T &key) {root = eraseNode(root, key);}

  T findStat(size_t k) {
    return findStatRec(root, k); 
  }

  ~AvlTree() {delete root;}

  AvlTree<T, Comparator>& operator=(const AvlTree<T, Comparator>& other) {
    if (this != &other) {
      delete root;
      root = nullptr;
      copyTree(other.root);
    }

    return *this;
  }
};

int main() {
  AvlTree<int> tree;
  size_t n = 0;
  std::cin >> n;
  for (size_t i = 0; i < n; ++i) {
    int num = 0;
    int k = 0;
    std::cin >> num >> k;
    if (num < 0) {
      tree.erase(-num);
    } else {
      tree.insert(num);
    }
    std::cout << tree.findStat(k) << std::endl;
  }
  AvlTree<int> b;
  b = tree;
}
