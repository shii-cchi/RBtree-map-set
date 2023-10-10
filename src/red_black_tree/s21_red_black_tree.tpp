#include "s21_red_black_tree.h"

namespace s21 {

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::RedBlackTree() : head(new Node), tree_size(0) {}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::RedBlackTree(const RedBlackTree &other)
    : RedBlackTree() {
  if (other.GetSize() != 0) {
    CopyTree(other);
  }
}

template <typename Key, typename Compare>
RedBlackTree<Key, Compare>::RedBlackTree(RedBlackTree &&other) noexcept
    : RedBlackTree() {
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
void RedBlackTree<Key, Compare>::SwapTree(RedBlackTree &other) noexcept {
  std::swap(head, other.head);
  std::swap(tree_size, other.tree_size);
  std::swap(cmp, other.cmp);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *
RedBlackTree<Key, Compare>::GetMinNode() const {
  return head->left;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *
RedBlackTree<Key, Compare>::GetMaxNode() const {
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
bool RedBlackTree<Key, Compare>::isEmpty() const noexcept {
  return !GetRoot();
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::size_type
RedBlackTree<Key, Compare>::GetMaxSize() const noexcept {
  return ((std::numeric_limits<size_type>::max() / 2) - sizeof(RedBlackTree) -
          sizeof(Node)) /
         sizeof(Node);
}

template <typename Key, typename Compare>
std::pair<typename RedBlackTree<Key, Compare>::iterator, bool>
RedBlackTree<Key, Compare>::Insert(const key_type key) {
  Node *new_node = new Node{key};

  auto res = InsertNode(GetRoot(), new_node);
  bool is_inserted = res.second;

  if (!is_inserted) {
    delete new_node;
  }

  return res;
}

template <typename Key, typename Compare>
std::pair<typename RedBlackTree<Key, Compare>::iterator, bool>
RedBlackTree<Key, Compare>::InsertNode(Node *root, Node *new_node) {
  if (!GetRoot()) {
    new_node->color = Color::kBlack;
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
  BalanceForInsert(new_node);

  return {iterator(new_node), true};
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::BalanceForInsert(Node *node) {
  while (node != GetRoot() && node->parent->color == Color::kRed) {
    Node *parent = node->parent;
    Node *grandparent = parent->parent;

    bool parentIsLeftChild = (grandparent->left == parent);
    Node *uncle = parentIsLeftChild ? grandparent->right : grandparent->left;

    if (uncle && uncle->color == Color::kRed) {
      parent->color = Color::kBlack;
      uncle->color = Color::kBlack;
      grandparent->color = Color::kRed;
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

      parent->color = Color::kBlack;
      grandparent->color = Color::kRed;
    }
  }

  GetRoot()->color = Color::kBlack;
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
    const_reference key) noexcept {
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
RedBlackTree<Key, Compare>::Begin() noexcept {
  return iterator(head->left);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::const_iterator
RedBlackTree<Key, Compare>::Begin() const noexcept {
  return const_iterator(head->left);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::iterator
RedBlackTree<Key, Compare>::End() noexcept {
  return iterator(head);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::const_iterator
RedBlackTree<Key, Compare>::End() const noexcept {
  return const_iterator(head);
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::Merge(RedBlackTree &other) {
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

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::Erase(iterator position) {
  Node *extracted_node = ExtractNode(position);

  delete extracted_node;
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *
RedBlackTree<Key, Compare>::ExtractNode(iterator pos) {
  if (pos == End()) {
    return nullptr;
  }

  Node *extracted_node = pos.node_;

  if (extracted_node->left && extracted_node->right) {
    Node *replace = SearchMinNode(extracted_node->right);
    SwapForErase(extracted_node, replace);
  }

  if (extracted_node->color == Color::kBlack &&
      ((!extracted_node->left && extracted_node->right) ||
       (extracted_node->left && !extracted_node->right))) {
    Node *replace;
    if (extracted_node->left) {
      replace = extracted_node->left;
    } else {
      replace = extracted_node->right;
    }
    SwapForErase(extracted_node, replace);
  }

  if (extracted_node->color == Color::kBlack && !extracted_node->left &&
      !extracted_node->right) {
    BalanceForErase(extracted_node);
  }

  ExtractFromTree(extracted_node);

  UpdateParam(extracted_node);

  return extracted_node;
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::ExtractFromTree(Node *node) {
  if (node == GetRoot()) {
    SetupHead();
  } else {
    if (node == node->parent->left) {
      node->parent->left = nullptr;
    } else {
      node->parent->right = nullptr;
    }
  }
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::UpdateParam(Node *node) {
  if (GetMinNode() == node) {
    SetMinNode(SearchMinNode(GetRoot()));
  }

  if (GetMaxNode() == node) {
    SetMaxNode(SearchMaxNode(GetRoot()));
  }

  --tree_size;

  node->ToDefault();
}

template <typename Key, typename Compare>
void RedBlackTree<Key, Compare>::SwapForErase(Node *node,
                                              Node *other) {
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

template <typename KeyType, typename Compare>
void RedBlackTree<KeyType, Compare>::SwapNode(Node *node_1,
                                              Node *node_2) {
  std::swap(node_1->parent, node_2->parent);
  std::swap(node_1->left, node_2->left);
  std::swap(node_1->right, node_2->right);
  std::swap(node_1->color, node_2->color);
}

template <typename KeyType, typename Compare>
void RedBlackTree<KeyType, Compare>::UpdateParent(Node *node) {
  if (node->left) {
    node->left->parent = node;
  }

  if (node->right) {
    node->right->parent = node;
  }
}

template <typename KeyType, typename Comparator>
void RedBlackTree<KeyType, Comparator>::BalanceForErase(
    Node *extracted_node) {
  Node *parent = extracted_node->parent;

  while (extracted_node != GetRoot() && extracted_node->color == Color::kBlack) {
    Node *sibling =
        (extracted_node == parent->left) ? parent->right : parent->left;

    if (sibling == parent->right) {
      if (isRed(sibling)) {
        std::swap(sibling->color, parent->color);
        RotateLeft(parent);
        parent = extracted_node->parent;
        sibling = parent->right;
      }

      if (!isRed(sibling) && IsChildrenBlack(sibling)) {
        sibling->color = Color::kRed;
        if (parent->color == Color::kRed) {
          parent->color = Color::kBlack;
          break;
        }
        extracted_node = parent;
        parent = extracted_node->parent;
      } else {
        if (IsLeftChildRed(sibling)) {
          std::swap(sibling->color, sibling->left->color);
          RotateRight(sibling);
          sibling = parent->right;
        }

        sibling->right->color = Color::kBlack;
        sibling->color = parent->color;
        parent->color = Color::kBlack;
        RotateLeft(parent);
        break;
      }
    } else {
      if (isRed(sibling)) {
        std::swap(sibling->color, parent->color);
        RotateRight(parent);
        parent = extracted_node->parent;
        sibling = parent->left;
      }

      if (!isRed(sibling) && IsChildrenBlack(sibling)) {
        sibling->color = Color::kRed;
        if (parent->color == Color::kRed) {
          parent->color = Color::kBlack;
          break;
        }
        extracted_node = parent;
        parent = extracted_node->parent;
      } else {
        if (IsRightChildRed(sibling)) {
          std::swap(sibling->color, sibling->right->color);
          RotateLeft(sibling);
          sibling = parent->left;
        }

        sibling->left->color = Color::kBlack;
        sibling->color = parent->color;
        parent->color = Color::kBlack;
        RotateRight(parent);
        break;
      }
    }
  }
}

template <typename KeyType, typename Compare>
bool RedBlackTree<KeyType, Compare>::isRed(Node *node) const {
  return node->color == Color::kRed;
}

template <typename KeyType, typename Compare>
bool RedBlackTree<KeyType, Compare>::IsChildrenBlack(
    Node *node) const {
  return (!node->left || node->left->color == Color::kBlack) &&
         (!node->right || node->right->color == Color::kBlack);
}

template <typename KeyType, typename Compare>
bool RedBlackTree<KeyType, Compare>::IsLeftChildRed(Node *node) const {
  return node->left && node->left->color == Color::kRed &&
         (!node->right || node->right->color == Color::kBlack);
}

template <typename KeyType, typename Compare>
bool RedBlackTree<KeyType, Compare>::IsRightChildRed(
    Node *node) const {
  return node->right && node->right->color == Color::kRed &&
         (!node->left || node->left->color == Color::kBlack);
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *
RedBlackTree<Key, Compare>::SearchMinNode(Node *node) const {
  while (true) {
    if (!node->left) return node;
    node = node->left;
  }
}

template <typename Key, typename Compare>
typename RedBlackTree<Key, Compare>::Node *
RedBlackTree<Key, Compare>::SearchMaxNode(Node *node) const {
  while (true) {
    if (!node->right) return node;
    node = node->right;
  }
}

template <typename KeyType, typename Compare>
bool RedBlackTree<KeyType, Compare>::CheckTree() const {
  if (!GetRoot()) {
    return true;
  }

  if (GetRoot()->color == Color::kRed) {
    return false;
  }

  if (head->color == Color::kBlack) {
    return false;
  }

  if (CheckRedNodes(GetRoot()) == false) {
    return false;
  }

  if (CheckBlackHeight(GetRoot()) == -1) {
    return false;
  }

  return true;
}

template <typename KeyType, typename Compare>
bool RedBlackTree<KeyType, Compare>::CheckRedNodes(
    const Node *node) const {
  if (node->color == Color::kRed) {
    if (node->left && node->left->color == Color::kRed) {
      return false;
    }
    if (node->right && node->right->color == Color::kRed) {
      return false;
    }
  }

  if (node->left) {
    if (!CheckRedNodes(node->left)) {
      return false;
    }
  }

  if (node->right) {
    if (!CheckRedNodes(node->right)) {
      return false;
    }
  }

  return true;
}

template <typename KeyType, typename Compare>
int RedBlackTree<KeyType, Compare>::CheckBlackHeight(
    const Node *node) const {
  if (!node) {
    return 0;
  }

  int left_height = CheckBlackHeight(node->left);
  int right_height = CheckBlackHeight(node->right);
  if (left_height == -1 || right_height == -1 || left_height != right_height) {
    return -1;
  } else {
    return left_height + (node->color == Color::kBlack ? 1 : 0);
  }
}

}  // namespace s21