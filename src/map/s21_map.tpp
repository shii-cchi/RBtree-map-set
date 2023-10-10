#include "s21_map.h"

namespace s21 {

template <typename Key, typename T>
map<Key, T>::map() : tree(new tree_type{}) {}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items) : map() {
  for (auto i : items) {
    insert(i);
  }
}

template <typename Key, typename T>
map<Key, T>::map(const map &other) : tree(new tree_type(*other.tree)) {}

template <typename Key, typename T>
map<Key, T>::map(map &&other) noexcept
    : tree(new tree_type(std::move(*other.tree))) {}

template <typename Key, typename T>
map<Key, T>::~map() {
  delete tree;
  tree = nullptr;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(const map &other) {
  *tree = *other.tree;
  return *this;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&other) noexcept {
  *tree = std::move(*other.tree);
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::at(const key_type &key) {
  iterator it = tree->Find({key, mapped_type{}});

  if (it == end()) {
    throw std::out_of_range("Element with the specified key not found");
  }

  return (*it).second;
}

template <typename Key, typename T>
const typename map<Key, T>::mapped_type &map<Key, T>::at(
    const key_type &key) const {
  return const_cast<map<Key, T> *>(this)->at(key);
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::operator[](
    const key_type &key) {
  iterator it_search = tree->Find({key, mapped_type{}});

  if (it_search == end()) {
    std::pair<iterator, bool> res = insert({key, mapped_type{}});
    return (*res.first).second;
  } else {
    return (*it_search).second;
  }
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() noexcept {
  return tree->Begin();
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::begin() const noexcept {
  return tree->Begin();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() noexcept {
  return tree->End();
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::end() const noexcept {
  return tree->End();
}

template <typename Key, typename T>
bool map<Key, T>::empty() const noexcept {
  return tree->isEmpty();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() const noexcept {
  return tree->GetSize();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() const noexcept {
  return tree->GetMaxSize();
}

template <typename Key, typename T>
void map<Key, T>::clear() noexcept {
  tree->RemoveTree();
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type &value) {
  return tree->Insert(value);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const key_type &key, const mapped_type &obj) {
  return tree->Insert(value_type{key, obj});
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  iterator it = tree->Find({key, mapped_type{}});

  if (it == end()) {
    return tree->Insert(value_type{key, obj});
  }

  (*it).second = obj;

  return {it, false};
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  tree->Erase(pos);
}

template <typename Key, typename T>
void map<Key, T>::swap(map &other) noexcept {
  tree->SwapTree(*other.tree);
}

template <typename Key, typename T>
void map<Key, T>::merge(map &other) {
  tree->Merge(*other.tree);
}

template <typename Key, typename T>
bool map<Key, T>::contains(const key_type &key) const {
  iterator it = tree->Find({key, mapped_type{}});

  return it != end();
}

template <typename Key, typename T>
bool map<Key, T>::operator==(const map &other) const {
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