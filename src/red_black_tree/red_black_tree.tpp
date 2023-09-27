#include "red_black_tree.h"

namespace s21 {

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::RedBlackTree() : head(new Node), tree_size(0) {}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::RedBlackTree(const RedBlackTree &other) : RedBlackTree() {
  if (other.GetSize() != 0) {
    CopyTree(other);
  }
}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::RedBlackTree(RedBlackTree &&other) noexcept  : RedBlackTree() {
  if (this != &other) {
    SwapTree(other);
  }
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::RedBlackTree &
RedBlackTree<Key, Compare>::operator=(const RedBlackTree &other) {
  if (this == &other) {
    return *this;
  }

  if (other.GetSize() != 0) {
    CopyTree(other);
  } else {
    RemoveTree();
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
void RedBlackTree<Key, Compare>::CopyTree(const RedBlackTree &other) {
  Node *copy = CopyNode(other.GetRoot(), other.GetRoot()->parent);

  RemoveTree();
  SetRoot(copy);
  GetRoot()->parent = head;
  SetMinNode(SearchMinNode(GetRoot()));
  SetMaxNode(SearchMaxNode(GetRoot()));
  tree_size = other.tree_size;
  cmp = other.cmp;
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
const typename RedBlackTree<Key, Compare>::Node *
RedBlackTree<Key, Compare>::GetRoot() const {
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
RedBlackTree<Key, Compare>::GetSize() const noexcept {
  return tree_size;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::SwapTree(RedBlackTree &other) {
  std::swap(head, other.head);
  std::swap(tree_size, other.tree_size);
  std::swap(cmp, other.cmp);
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
  return !GetRoot();
}

template <typename Key, typename Comparator>
typename RedBlackTree<Key, Comparator>::size_type
RedBlackTree<Key, Comparator>::MaxSize() const noexcept {
  return ((std::numeric_limits<size_type>::max() / 2) - sizeof(RedBlackTree) -
          sizeof(Node)) /
         sizeof(Node);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::Insert(const key_type key) {
  Node *new_node = new Node{key};

  auto res = InsertNode(head->parent, new_node);
  iterator it = res.first;
  bool is_inserted = res.second;

  if (!is_inserted) {
    delete new_node;
  }

  return it;
}

template <typename Key, typename Compare>
std::pair<typename RedBlackTree<Key, Compare>::iterator, bool>
RedBlackTree<Key, Compare>::InsertNode(Node *root, Node *new_node) {
  if (!GetRoot()) {
    new_node->color = kBlack;
    new_node->parent = head;
    SetRoot(new_node);
    UpdateSizeAndMinMaxNode(new_node);
    return {iterator(new_node), true};
  }

  Node *node = root;
  Node *parent = nullptr;

  while (node) {
    parent = node;
    if (cmp(new_node->key, node->key)) {
      node = node->left;
    } else {
      if (cmp(node->key, new_node->key)) {
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
  UpdateSizeAndMinMaxNode(new_node);
  BalanceTree(new_node);

  return {iterator(new_node), true};
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::BalanceTree(Node *node) {
  while (node != GetRoot() && node->parent->color == kRed) {
    Node *parent = node->parent;
    Node *grandparent = parent->parent;

    bool parentIsLeftChild = (grandparent->left == parent);
    Node *uncle = parentIsLeftChild ? grandparent->right : grandparent->left;

    if (uncle && uncle->color == kRed) {
      parent->color = kBlack;
      uncle->color = kBlack;
      grandparent->color = kRed;
      node = grandparent;
      parent = node->parent;
    } else {
      if (parentIsLeftChild != (node == parent->left)) {
        if (parentIsLeftChild) {
          RotateLeft(parent);
        } else {
          RotateRight(parent);
        }
        std::swap(parent, node);
      }

      if (parentIsLeftChild) {
        RotateRight(grandparent);
      } else {
        RotateLeft(grandparent);
      }

      parent->color = kBlack;
      grandparent->color = kRed;
    }
  }

  GetRoot()->color = kBlack;
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
void RedBlackTree<Key, Compare>::UpdateSizeAndMinMaxNode(Node *new_node) {
  tree_size++;

  if (GetMinNode() == head || GetMinNode()->left) {
    SetMinNode(new_node);
  }

  if (GetMaxNode() == head || GetMaxNode()->right) {
    SetMaxNode(new_node);
  }
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
  Node *current = GetRoot();
  Node *res = End().node_;

  while (current) {
    if (!cmp(current->key, key)) {
      res = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return iterator(res);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::UpperBound(const_reference key) {
  Node *current = GetRoot();
  Node *res = End().node;

  while (current) {
    if (cmp(current->key, key)) {
      res = current;
      current = current->left;
    } else {
      current = current->right;
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

template <typename Key, typename Comparator>
void RedBlackTree<Key, Comparator>::Merge(RedBlackTree &other) {
  if (this != &other) {
    iterator other_begin = other.Begin();
    iterator other_end = other.End();

    while (other_begin != other_end) {
      const Key &current_key = other_begin.node_->key;
      iterator it = Find(current_key);

      if (it == End()) {
        iterator tmp = other_begin;
        ++other_begin;
        Node *moving_node = other.ExtractNode(tmp);
        InsertNode(GetRoot(), moving_node);
      } else {
        ++other_begin;
      }
    }
  }
}

template <typename Key, typename Comparator>
void RedBlackTree<Key, Comparator>::Erase(iterator position) noexcept {
  Node *extracted_node = ExtractNode(position);

  delete extracted_node;
}

template <typename Key, typename Comparator>
typename RedBlackTree<Key, Comparator>::Node *
RedBlackTree<Key, Comparator>::ExtractNode(iterator position) noexcept {
  if (position == End()) {
    return nullptr;
  }

  Node *extracted_node = position.node_;

  if (extracted_node->left && extracted_node->right) {
    PrepareNodeWithTwoChildren(extracted_node);
  } else if (!extracted_node->left && !extracted_node->right) {
    PrepareNodeWithoutChildren(extracted_node);
  } else {
    PrepareNodeWithOneChild(extracted_node);
  }

  ExtractFromTree(extracted_node);

  tree_size--;
  extracted_node->ToDefault();

  return extracted_node;
}

template <typename Key, typename Comparator>
void RedBlackTree<Key, Comparator>::PrepareNodeWithTwoChildren(Node *node) {
  Node *replace = SearchMinNode(node->right);
  SwapForErase(node, replace);
}

template <typename Key, typename Comparator>
void RedBlackTree<Key, Comparator>::PrepareNodeWithoutChildren(Node *node) {
  if (node->color == kBlack) {
    BalanceForErase(node);
  }
}

template <typename Key, typename Comparator>
void RedBlackTree<Key, Comparator>::PrepareNodeWithOneChild(Node *node) {
  Node *child = (node->left) ? node->left : node->right;
  SwapForErase(node, child);
}

template <typename Key, typename Comparator>
void RedBlackTree<Key, Comparator>::ExtractFromTree(Node *node) {
  if (node == GetRoot()) {
    SetupHead();
  } else {
    if (node == node->parent->left) {
      node->parent->left = nullptr;
    } else {
      node->parent->right = nullptr;
    }

    if (GetMinNode() == node) {
      SetMinNode(SearchMinNode(GetRoot()));
    }

    if (GetMaxNode() == node) {
      SetMaxNode(SearchMaxNode(GetRoot()));
    }
  }
}

template <typename Key, typename Comparator>
void RedBlackTree<Key, Comparator>::SwapForErase(Node *node,
                                                 Node *other) noexcept {
  if (other->parent->left == other) {
    other->parent->left = node;
  } else {
    other->parent->right = node;
  }

  if (node == GetRoot()) {
    SetRoot(other);
  } else {
    if (node->parent->left == node) {
      node->parent->left = other;
    } else {
      node->parent->right = other;
    }
  }

  SwapNode(node, other);

  UpdateParent(node);
  UpdateParent(other);
}

template <typename KeyType, typename Comparator>
void RedBlackTree<KeyType, Comparator>::SwapNode(Node *node_1,
                                                 Node *node_2) noexcept {
  std::swap(node_1->parent, node_2->parent);
  std::swap(node_1->left, node_2->left);
  std::swap(node_1->right, node_2->right);
  std::swap(node_1->color, node_2->color);
}

template <typename KeyType, typename Comparator>
void RedBlackTree<KeyType, Comparator>::UpdateParent(Node *node) noexcept {
  if (node->left) {
    node->left->parent = node;
  }

  if (node->right) {
    node->right->parent = node;
  }
}

template <typename KeyType, typename Comparator>
void RedBlackTree<KeyType, Comparator>::BalanceForErase(
    Node *extracted_node) noexcept {
  while (extracted_node != GetRoot() && extracted_node->color == kBlack) {
    Node *parent = extracted_node->parent;
    Node *sibling =
        (extracted_node == parent->left) ? parent->right : parent->left;

    if (isRed(sibling)) {
      BalanceRedSibling(sibling, extracted_node, parent);
    }

    if (!isRed(sibling) && IsChildrenBlack(sibling)) {
      bool is_balanced =
          BalanceBlackSiblingWithBlackChildren(sibling, extracted_node, parent);
      if (is_balanced) {
        break;
      }
    } else {
      BalanceBlackSiblingWithOneBlackChild(sibling, extracted_node, parent);
      break;
    }
  }
}

template <typename KeyType, typename Comparator>
void RedBlackTree<KeyType, Comparator>::BalanceRedSibling(
    Node *sibling, Node *extracted_node, Node *parent) noexcept {
  std::swap(sibling->color, parent->color);
  if (extracted_node == parent->left) {
    RotateLeft(parent);
    parent = extracted_node->parent;
    sibling = parent->right;
  } else {
    RotateRight(parent);
    parent = extracted_node->parent;
    sibling = parent->left;
  }
}

template <typename KeyType, typename Comparator>
bool RedBlackTree<KeyType, Comparator>::BalanceBlackSiblingWithBlackChildren(
    Node *sibling, Node *extracted_node, Node *parent) noexcept {
  sibling->color = kRed;
  if (parent->color == kRed) {
    parent->color = kBlack;
    return true;
  }

  extracted_node = parent;
  parent = extracted_node->parent;
  return false;
}

template <typename KeyType, typename Comparator>
void RedBlackTree<KeyType, Comparator>::BalanceBlackSiblingWithOneBlackChild(
    Node *sibling, Node *extracted_node, Node *parent) noexcept {
  if (extracted_node == parent->left) {
    if (IsLeftChildRed(sibling)) {
      std::swap(sibling->color, sibling->left->color);
      RotateRight(sibling);
      sibling = parent->right;
    }

    sibling->right->color = kBlack;
    sibling->color = parent->color;
    parent->color = kBlack;
    RotateLeft(parent);
  } else {
    if (IsRightChildRed(sibling)) {
      std::swap(sibling->color, sibling->right->color);
      RotateLeft(sibling);
      sibling = parent->left;
    }

    sibling->left->color = kBlack;
    sibling->color = parent->color;
    parent->color = kBlack;
    RotateRight(parent);
  }
}

template <typename KeyType, typename Comparator>
bool RedBlackTree<KeyType, Comparator>::isRed(Node *node) noexcept {
  return node->color == kRed;
}

template <typename KeyType, typename Comparator>
bool RedBlackTree<KeyType, Comparator>::IsChildrenBlack(
    Node *node) const noexcept {
  return (!node->left || node->left->color == kBlack) &&
         (!node->right || node->right->color == kBlack);
}

template <typename KeyType, typename Comparator>
bool RedBlackTree<KeyType, Comparator>::IsLeftChildRed(
    Node *node) const noexcept {
  return node->left && node->left->color == kRed &&
         (!node->right || node->right->color == kBlack);
}

template <typename KeyType, typename Comparator>
bool RedBlackTree<KeyType, Comparator>::IsRightChildRed(
    Node *node) const noexcept {
  return node->right && node->right->color == kRed &&
         (!node->left || node->left->color == kBlack);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *
RedBlackTree<Key, Compare>::SearchMinNode(Node *node) const noexcept {
  while (true) {
    if (!node->left) return node;
    node = node->left;
  }
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *
RedBlackTree<Key, Compare>::SearchMaxNode(Node *node) const noexcept {
  while (true) {
    if (!node->right) return node;
    node = node->right;
  }
}

}  // namespace s21