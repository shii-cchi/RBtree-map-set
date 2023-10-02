#include "s21_set.h"

namespace s21 {

template <typename Key>
set<Key>::set() : tree(new tree_type{}) {}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const &items) : set() {
  for (auto i : items) {
    insert(i);
  }
}

template <typename Key>
set<Key>::set(const set &other) : tree(new tree_type(*other.tree)) {}

template <typename Key>
set<Key>::set(set &&other) noexcept
    : tree(new tree_type(std::move(*other.tree))) {}

template <typename Key>
set<Key>::~set() {
  delete tree;
  tree = nullptr;
}

template <typename Key>
set<Key> &set<Key>::operator=(const set &other) {
  *tree = *other.tree;
  return *this;
}

template <typename Key>
set<Key> &set<Key>::operator=(set &&other) noexcept {
  *tree = std::move(*other.tree);
  return *this;
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() noexcept {
  return tree->Begin();
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::begin() const noexcept {
  return tree->Begin();
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() noexcept {
  return tree->End();
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::end() const noexcept {
  return tree->End();
}

template <typename Key>
bool set<Key>::empty() const noexcept {
  return tree->isEmpty();
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() const noexcept {
  return tree->GetSize();
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() const noexcept {
  return tree->GetMaxSize();
}

template <typename Key>
void set<Key>::clear() noexcept {
  tree->RemoveTree();
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type &value) {
  return tree->Insert(value);
}

template <typename Key>
void set<Key>::erase(iterator pos) noexcept {
  tree->Erase(pos);
}

template <typename Key>
void set<Key>::swap(set &other) noexcept {
  tree->SwapTree(*other.tree);
}

template <typename Key>
void set<Key>::merge(set &other) noexcept {
  tree->Merge(*other.tree);
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const key_type &key) const noexcept {
    return tree->Find(key);
}

template <typename Key>
bool set<Key>::contains(const key_type &key) const noexcept {
  iterator it = tree->Find(key);

  return it != end();
}

template <typename Key>
bool set<Key>::operator==(const set &other) const {
  if (this == &other) return true;

  if (size() != other.size()) return false;

  auto it_1 = begin();
  auto it_2 = other.begin();

  while (it_1 != end()) {
    if (*it_1 != *it_2) return false;

    ++it_1;
    ++it_2;
  }

  return true;
}


}  // namespace s21