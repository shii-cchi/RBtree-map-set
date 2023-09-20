#include "red_black_tree.h"

namespace s21 {

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::RedBlackTree() : head(new Node), tree_size(0) {}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::RedBlackTree(const RedBlackTree &other) {
    if (other.GetSize() != 0) {
        CopyTree(other);
    }
}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::RedBlackTree(RedBlackTree &&other) noexcept {
    // Swap(other);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::RedBlackTree &
RedBlackTree<Key, Compare>::operator=(const RedBlackTree &other) {
    if (this != &other) {
        if (other.GetSize() != 0) {
            CopyTree(other);
        } else {
            RemoveTree();
        }
    }

    return *this;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::RedBlackTree &
RedBlackTree<Key, Compare>::operator=(RedBlackTree &&other) noexcept {
    RemoveTree();
    Swap(other);
    return *this;
}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::~RedBlackTree() {
    RemoveTree();
    delete head;
    head = nullptr;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::CopyTree(Node *node) {
    Node *copy = CopyNode(node.Root(), node.Root()->parent);

    RemoveTree();
    SetRoot(copy);
    Root()->parent = head;
    tree_size = node.tree_size;
    cmp = node.cmp;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *RedBlackTree<Key, Compare>::CopyNode(
    const Node *node, Node *parent) {
  Node *copy = new Node{node->key, node->color};

  try {
    if (node->left) {
      copy->left = CopyNode(node->left, copy)
    }

    if (node->right) {
      copy->right = CopyNode(node->rigth, copy)
    }
  } catch {
    RemoveNode(copy);
    throw;
  }

  copy->parent = parent;
  return copy;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::RemoveNode(Node *node) {
  if (!node) {
    return;
  }

  RemoveNode(node->left);
  RemoveNode(node->rigth);
  delete node;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::RemoveTree() {
  RemoveNode(GetRoot());
  SetHead();
  tree_size = 0;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *
RedBlackTree<Key, Compare>::GetRoot() {
  return head->parent;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::SetHead() {
  SetRoot(nullptr);
  // // Т.к. элементов нет, то самый маленький (самый левый) элемент будет
  // // указывать на голову
  // MostLeft() = head_;
  // // Т.к. элементов нет, то самый большой (самый правый) элемент будет
  // // указывать на голову
  // MostRight() = head_;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::SetRoot(Node *node) {
  head->parent = node;
}

template <typename Key, typename Compare>
size_type RedBlackTree<Key, Compare>::GetSize() {
  return tree_size;
}

}  // namespace s21