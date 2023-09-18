#include "node.h"

namespace s21 {
    
template <typename key_type>
Node<key_type>::Node()
    : parent_(nullptr), left_(this), right_(this), key_(key_type{}), color_(RED) {}

template <typename key_type>
Node<key_type>::Node(const key_type &key)
    : parent_(nullptr), left_(nullptr), right_(nullptr), key_(key), color_(RED) {}

template <typename key_type>
Node<key_type>::Node(key_type &&key)
    : parent_(nullptr), left_(nullptr), right_(nullptr), key_(std::move(key)), color_(RED) {}

template <typename key_type>
Node<key_type>::Node(key_type key, Color color)
    : parent_(nullptr), left_(nullptr), right_(nullptr), key_(key), color_(color) {}

template <typename key_type>
void Node<key_type>::ToDefault() noexcept {
    left_ = nullptr;
    right_ = nullptr;
    parent_ = nullptr;
    color_ = RED;
}

template <typename key_type>
Node<key_type> *Node<key_type>::NextNode() const noexcept {
    auto *node = const_cast<RedBlackTreeNode *>(this);
    if (node->color_ == RED &&
        (node->parent_ == nullptr || node->parent_->parent_ == node)) {
        node = node->left_;
    }
    else if (node->right_ != nullptr) {
        node = node->right_;

        while (node->left_ != nullptr) {
            node = node->left_;
        }
    }
    else {
        RedBlackTreeNode *parent = node->parent_;

        while (node == parent->right_) {
            node = parent;
            parent = parent->parent_;
        }
        if (node->right_ != parent) {
            node = parent;
        }
    }

    return node;
}

template <typename key_type>
Node<key_type> *Node<key_type>::PrevNode() const noexcept {
    RedBlackTreeNode *node = const_cast<RedBlackTreeNode *>(this);

    if (node->color_ == RED &&
        (node->parent_ == nullptr || node->parent_->parent_ == node)) {
        node = node->right_;
    }
    else if (node->left_ != nullptr) {
        node = node->left_;
        while (node->right_ != nullptr) {
            node = node->right_;
        }
    }
    else {
        RedBlackTreeNode *parent = node->parent_;
        while (node == parent->left_) {
            node = parent;
            parent = parent->parent_;
        }
        if (node->left_ != parent) {
            node = parent;
        }
    }

    return node;
}

}
