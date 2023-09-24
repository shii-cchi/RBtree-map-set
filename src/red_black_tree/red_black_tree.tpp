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
  SwapTree(other);
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
  SwapTree(other);
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
  GetRoot()->parent = head;
  tree_size = node.tree_size;
  cmp = node.cmp;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *RedBlackTree<Key, Compare>::CopyNode(
    const Node *node, Node *parent) {
  Node *copy = new Node{node->key, node->color};

  try {
    if (node->left) {
      copy->left = CopyNode(node->left, copy);
    }

    if (node->right) {
      copy->right = CopyNode(node->right, copy);
    }
  } catch (...) {
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
  RemoveNode(node->right);
  delete node;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::RemoveTree() {
  RemoveNode(GetRoot());
  SetupHead();
  tree_size = 0;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *
RedBlackTree<Key, Compare>::GetRoot() {
  return head->parent;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::SetRoot(Node *node) {
  head->parent = node;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::SetupHead() {
  SetRoot(nullptr);
  SetMinNode(head);
  SetMaxNode(head);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::size_type
RedBlackTree<Key, Compare>::GetSize() {
  return tree_size;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::SwapTree(Node *node) {
  std::swap(head, node.head);
  std::swap(tree_size, node.tree_size);
  std::swap(cmp, node.cmp);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *
RedBlackTree<Key, Compare>::GetMinNode() {
  return head->left;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *
RedBlackTree<Key, Compare>::GetMaxNode() {
  return head->right;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::SetMinNode(Node *node) {
  head->left = node;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::SetMaxNode(Node *node) {
  head->right = node;
}

template <typename Key, typename Compare>
bool RedBlackTree<Key, Compare>::isEmpty() {
  return tree_size == 0;
}

template <typename Key, typename Comparator>
typename RedBlackTree<Key, Comparator>::size_type
RedBlackTree<Key, Comparator>::MaxSize() const noexcept {
  return ((std::numeric_limits<size_type>::max() / 2) - sizeof(RedBlackTree) - sizeof(Node)) / sizeof(Node);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::Insert(const key_type key) {
  Node *new_node = new Node{key};
  iterator it = InsertNode(head->parent, new_node).first;
  BalanceTree(new_node);  // надо ли переместить в инсертноде, меняется ли
                          // итератор после балансировки я хз
  return it;
}

template <typename Key, typename Compare>
std::pair<typename RedBlackTree<Key, Compare>::iterator, bool>
RedBlackTree<Key, Compare>::InsertNode(Node *root, Node *new_node) {
  Node *node = root;
  Node *parent = nullptr;

  if (!GetRoot()) {
    new_node->color = kBlack;
    new_node->parent = head;
    SetRoot(new_node);
  } else {
    while (node) {
      parent = node;

      if (cmp(new_node->key, node->key)) {
        node = node->left;
      } else {
        if (cmp_(node->key, new_node->key)) {
          node = node->right;
        } else {
          return {iterator(node), false};
        }
      }
    }

    new_node->parent = parent;
    if (cmp(new_node->key, parent->key)) {
      parent->left = new_node;
    } else {
      parent->right = new_node;
    }
  }

  tree_size++;

  if (GetMinNode() == head || GetMinNode()->left) {
    SetMinNode(new_node);
  }

  if (GetMaxNode() == head || GetMaxNode()->right) {
    SetMaxNode(new_node);
  }
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::BalanceTree(Node *node) {
  Node *parent = node->parent;

  while (node != GetRoot() && parent->color == kRed) {
    Node *grandparent = parent->parent;

    if (grandparent->left == parent) {
      Node *uncle = grandparent->right;

      if (uncle != nullptr && uncle->color == kRed) {
        parent->color = kBlack;
        grandparent->color = kRed;
        uncle->color = kBlack;

        node = grandparent;
        parent = node->parent;
      } else {
        if (parent->right == node) {
          RotateLeft(parent);
          std::swap(parent, node);
        }

        RotateRight(grandparent);
        grandparent->color = kRed;
        parent->color = kBlack;
        break;
      }
    } else {
      Node *uncle = grandparent->left;

      if (uncle != nullptr && uncle->color == kRed) {
        parent->color = kBlack;
        grandparent->color = kRed;
        uncle->color = kBlack;

        node = grandparent;
        parent = node->parent;
      } else {
        if (parent->left == node) {
          RotateRight(parent);
          std::swap(parent, node);
        }

        RotateLeft(grandparent);
        grandparent->color = kRed;
        parent->color = kBlack;
        break;
      }
    }

    GetRoot()->color = kBlack;
  }
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::RotateLeft(Node *node) {
  Node *pivot = node->right;

  pivot->parent = node->parent;

  if (node == GetRoot()) {
    SetRoot(pivot);
  } else if (node->parent->left == node) {
    node->parent->left = pivot;
  } else {
    node->parent->right = pivot;
  }

  node->right = pivot->left;
  if (pivot->left) {
    pivot->left->parent = node;
  }

  node->parent = pivot;
  pivot->left = node;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::RotateRight(Node *node) {
  Node *pivot = node->left;

  pivot->parent = node->parent;

  if (node == GetRoot()) {
    SetRoot(pivot);
  } else if (node->parent->left == node) {
    node->parent->left = pivot;
  } else {
    node->parent->right = pivot;
  }

  node->left = pivot->right;
  if (pivot->right) {
    pivot->right->parent = node;
  }

  node->parent = pivot;
  pivot->right = node;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator RedBlackTree<Key, Compare>::Find(
    const_reference key) {
  iterator res = LowerBound(key);

  if (res == End() || cmp(key, *res)) {
    return End();
  }

  return res;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::LowerBound(const_reference key) {
  Node *start = GetRoot();

  Node *res = End().node;

  while (start) {
    if (!cmp(start->key, key)) {
      res = start;
      start = start->left;
    } else {
      start = start->right;
    }
  }

  return iterator(res);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::UpperBound(const_reference key) {
  Node *start = GetRoot();

  Node *res = End().node;

  while (start) {
    if (!cmp(key, start->key)) {
      res = start;
      start = start->left;
    } else {
      start = start->right;
    }
  }

  return iterator(res);
}

template <typename Key, typename Comparator>
typename RedBlackTree<Key, Comparator>::iterator
RedBlackTree<Key, Comparator>::Begin() noexcept {
  return iterator(head->left);
}

template <typename Key, typename Comparator>
typename RedBlackTree<Key, Comparator>::const_iterator
RedBlackTree<Key, Comparator>::Begin() const noexcept {
  return const_iterator(head->left);
}

template <typename Key, typename Comparator>
typename RedBlackTree<Key, Comparator>::iterator
RedBlackTree<Key, Comparator>::End() noexcept {
  return iterator(head);
}

template <typename Key, typename Comparator>
typename RedBlackTree<Key, Comparator>::const_iterator
RedBlackTree<Key, Comparator>::End() const noexcept {
  return const_iterator(head);
}

}  // namespace s21