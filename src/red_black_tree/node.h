#ifndef CPP2_S21_CONTAINERS_RED_BLACK_TREE_NODE_H_
#define CPP2_S21_CONTAINERS_RED_BLACK_TREE_NODE_H_

namespace s21 {

enum Color { RED, BLACK };

template <typename key_type>
struct Node {
    Node();
    explicit Node(const key_type &key);
    explicit Node(key_type &&key);
    Node(key_type key, Color color);
    void ToDefault() noexcept;
    Node *NextNode() const noexcept;
    Node *PrevNode() const noexcept;

    Node *parent_;
    Node *left_;
    Node *right_;
    key_type key_;
    Color color_;
};

}  // namespase s21

#endif  // CPP2_S21_CONTAINERS_RED_BLACK_TREE_NODE_H_