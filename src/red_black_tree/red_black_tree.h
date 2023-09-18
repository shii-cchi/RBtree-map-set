#ifndef CPP2_S21_CONTAINERS_RED_BLACK_TREE_RED_BLACK_TREE_H_
#define CPP2_S21_CONTAINERS_RED_BLACK_TREE_RED_BLACK_TREE_H_

#include <functional>

#include "node.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>>
class RedBlackTree {
 private:
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

 private:
    Node *head_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_RED_BLACK_TREE_RED_BLACK_TREE_H_