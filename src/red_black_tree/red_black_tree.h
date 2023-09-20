#ifndef CPP2_S21_CONTAINERS_RED_BLACK_TREE_RED_BLACK_TREE_H_
#define CPP2_S21_CONTAINERS_RED_BLACK_TREE_RED_BLACK_TREE_H_

#include <functional>

namespace s21 {

enum Color { kRed, kBlack };

template <typename Key, typename Compare = std::less<Key>>
class RedBlackTree {
 private:
  struct Node;
  struct Iterator;
  struct IteratorConst;

 public:
  using key_type = Key;
  using reference = key_type &;
  using const_reference = const key_type &;
  using iterator = Iterator;
  using const_iterator = IteratorConst;
  using size_type = std::size_t;

  RedBlackTree();
  RedBlackTree(const RedBlackTree &other);
  RedBlackTree(RedBlackTree &&other) noexcept;
  RedBlackTree &operator=(const RedBlackTree &other);
  RedBlackTree &operator=(RedBlackTree &&other) noexcept;
  ~RedBlackTree();

  void CopyTree(Node *node);
  Node *CopyNode(const Node *node, Node *parent);
  void RemoveNode(Node *node);
  void RemoveTree();
  Node *GetRoot();
  void SetRoot(Node *node);
  void SetHead();
  size_type GetSize();

  struct Node {
    Node()
        : parent(nullptr),
          left(this),
          right(this),
          key(key_type{}),
          color(kRed) {}

    Node(const key_type &key)
        : parent(nullptr),
          left(nullptr),
          right(nullptr),
          key(key),
          color(kRed) {}

    Node(key_type &&key)
        : parent(nullptr),
          left(nullptr),
          right(nullptr),
          key(std::move(key)),
          color(kRed) {}

    Node(key_type key, Color color)
        : parent(nullptr),
          left(nullptr),
          right(nullptr),
          key(key),
          color(color) {}

    void ToDefault() noexcept {
      left = nullptr;
      right = nullptr;
      parent = nullptr;
      color = kRed;
    }

    GetNextNode() const noexcept {
      Node *node = const_cast<Node *>(this);
      if (node->color == kRed &&
          (node->parent == nullptr || node->parent->parent == node)) {
        node = node->left;
      } else if (node->right != nullptr) {
        node = node->right;

        while (node->left != nullptr) {
          node = node->left;
        }
      } else {
        Node *parent = node->parent;

        while (node == parent->right) {
          node = parent;
          parent = parent->parent;
        }
        if (node->right != parent) {
          node = parent;
        }
      }

      return node;
    }

    GetPreviousNode() const noexcept {
      Node *node = const_cast<Node *>(this);

      if (node->color == kRed &&
          (node->parent == nullptr || node->parent->parent == node)) {
        node = node->right;
      } else if (node->left != nullptr) {
        node = node->left;
        while (node->right != nullptr) {
          node = node->right;
        }
      } else {
        Node *parent = node->parent;
        while (node == parent->left) {
          node = parent;
          parent = parent->parent;
        }
        if (node->left != parent) {
          node = parent;
        }
      }
      return node;
    }

    Node *parent;
    Node *left;
    Node *right;
    key_type key;
    Color color;
  };

 private:
  Node *head;
  size_type tree_size;
  Compare cmp;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_RED_BLACK_TREE_RED_BLACK_TREE_H_