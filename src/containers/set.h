#ifndef CONTAINERS_SET_SET_H_
#define CONTAINERS_SET_SET_H_

#include "red_black_tree/red_black_tree.h"

namespace RBtreeMapSet {

template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;

  using tree_type = RedBlackTree<value_type>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;
  using size_type = std::size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &other);
  set(set &&other) noexcept;
  ~set();

  set &operator=(const set &other);
  set &operator=(set &&other) noexcept;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type &value);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  void erase(iterator pos);
  void swap(set &other) noexcept;
  void merge(set &other);

  iterator find(const key_type &key) const;
  bool contains(const key_type &key) const;

  bool operator==(const set &other) const;

 private:
  RedBlackTree<value_type> *tree;
};

}  // namespace RBtreeMapSet

#include "set.tpp"
#endif  // CONTAINERS_SET_SET_H_