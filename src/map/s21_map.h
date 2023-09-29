#ifndef CPP2_S21_CONTAINERS_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_MAP_S21_MAP_H_

#include <stdexcept>

#include "../red_black_tree/s21_red_black_tree.h"
#include "../red_black_tree/s21_red_black_tree.tpp"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;

  struct MapCompare {
    bool operator()(const_reference value_1,
                    const_reference value_2) const noexcept {
      return value_1.first < value_2.first;
    }
  };

  using tree_type = RedBlackTree<value_type, MapCompare>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;
  using size_type = std::size_t;

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &other);
  map(map &&other) noexcept;
  ~map();

  map &operator=(const map &other);
  map &operator=(map &&other) noexcept;

  mapped_type &at(const key_type &key);
  const mapped_type &at(const key_type &key) const;
  mapped_type &operator[](const key_type &key);

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
  void erase(iterator pos) noexcept;
  void swap(map &other) noexcept;
  void merge(map &other) noexcept;

  bool contains(const key_type &key) const noexcept;

  // bool operator==(const map &other) const;
 private:
  RedBlackTree<value_type, MapCompare> *tree;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_MAP_S21_MAP_H_